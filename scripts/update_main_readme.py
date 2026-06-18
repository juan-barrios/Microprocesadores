#!/usr/bin/env python3
"""Update the main README.md from every nested README.md in the repo.

The script scans the repository for README.md files inside practice/project folders
and rebuilds only the block delimited by AUTO-GENERATED-PRACTICES markers.
"""

from __future__ import annotations

import re
from pathlib import Path
from urllib.parse import quote

ROOT = Path(__file__).resolve().parents[1]
MAIN_README = ROOT / "README.md"

START_MARKER = "<!-- AUTO-GENERATED-PRACTICES:START -->"
END_MARKER = "<!-- AUTO-GENERATED-PRACTICES:END -->"

IGNORED_DIRS = {
    ".git",
    ".github",
    ".idea",
    ".vscode",
    "build",
    "dist",
    "debug",
    "release",
    "node_modules",
    "scripts",
}

SUBJECT_WORDS = (
    "Microprocesadores",
    "Microcrontoladores",  # typo present in an existing local README
)

KEYWORDS = [
    ("PIC16F887", "PIC16F887"),
    ("MPLAB", "MPLAB X"),
    ("Proteus", "Proteus"),
    ("XC8", "XC8"),
    ("7 segmentos", "7 segmentos"),
    ("7-segment", "7 segmentos"),
    ("display", "Display"),
    ("matriz", "Matriz LED"),
    ("LED", "LED"),
    ("ADC", "ADC"),
    ("PWM", "PWM"),
    ("Timer", "Timers"),
    ("interrup", "Interrupciones"),
    ("USART", "USART"),
    ("EUSART", "EUSART"),
]


def normalize_spaces(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


def strip_markdown(text: str) -> str:
    text = re.sub(r"!\[[^\]]*\]\([^)]*\)", "", text)
    text = re.sub(r"\[([^\]]+)\]\([^)]*\)", r"\1", text)
    text = re.sub(r"<[^>]+>", "", text)
    text = text.replace("`", "")
    text = text.strip(" -*_#|\t")
    return normalize_spaces(text)


def clean_description_text(text: str) -> str:
    """Remove course label words from generated summaries."""
    cleaned = text
    for word in SUBJECT_WORDS:
        cleaned = re.sub(rf"\b{re.escape(word)}\b", "", cleaned, flags=re.IGNORECASE)
    return normalize_spaces(cleaned)


def escape_table_cell(text: str) -> str:
    return text.replace("|", "\\|")


def humanize_folder_name(path: Path) -> str:
    name = path.parent.name.replace("_", " ").replace("-", " ")
    return normalize_spaces(name).title() or path.parent.as_posix()


def normalize_item_label(raw_label: str | None) -> str:
    if raw_label and raw_label.lower().startswith(("proy", "project")):
        return "Proyecto"
    return "Práctica"


def extract_title(readme_path: Path, text: str) -> str:
    h1_match = re.search(r"<h1[^>]*>(.*?)</h1>", text, flags=re.IGNORECASE | re.DOTALL)
    if h1_match:
        title = strip_markdown(h1_match.group(1))
        if title:
            return title

    for line in text.splitlines():
        match = re.match(r"^#\s+(.+)$", line.strip())
        if match:
            title = strip_markdown(match.group(1))
            if title:
                return title

    return humanize_folder_name(readme_path)


def extract_item_metadata(readme_path: Path, text: str = "") -> tuple[str, int | None]:
    """Return whether the README describes a Práctica or Proyecto and its number.

    Only the README header and the folder path are scanned for numbers. This avoids
    accidentally reading image dimensions, dates, or GitHub attachment IDs as the
    activity/project number.
    """
    rel = readme_path.relative_to(ROOT).as_posix()
    header_text = "\n".join(text.splitlines()[:40])

    labeled_pattern = re.compile(
        r"\b(pr[aá]ctica|practica|proyecto|project)\s*#?\s*(\d+)\b",
        flags=re.IGNORECASE,
    )

    for source in (header_text, rel):
        match = labeled_pattern.search(source)
        if match:
            label = normalize_item_label(match.group(1))
            return label, int(match.group(2))

    folder_pattern = re.compile(
        r"(?:^|/)(pr[aá]ctica|practica|proyecto|project)[ _.-]*(\d+)",
        flags=re.IGNORECASE,
    )
    match = folder_pattern.search(rel)
    if match:
        label = normalize_item_label(match.group(1))
        return label, int(match.group(2))

    title = extract_title(readme_path, text) if text else humanize_folder_name(readme_path)
    label = "Proyecto" if re.search(r"\bproyecto\b", title, flags=re.IGNORECASE) else "Práctica"
    number_match = re.search(r"(?:^|/)(\d+)(?:[^0-9]|$)", rel)
    number = int(number_match.group(1)) if number_match else None
    return label, number


def format_item_title(readme_path: Path, title: str, text: str) -> str:
    label, number = extract_item_metadata(readme_path, text)
    title = clean_description_text(title)
    title = re.sub(
        r"\b(pr[aá]ctica|practica|proyecto|project)\s*#?\s*\d+\b",
        "",
        title,
        flags=re.IGNORECASE,
    )
    title = normalize_spaces(title).upper()

    if number is None:
        return f"{label} - {title}"
    return f"{label} #{number} - {title}"


def should_skip_description_line(cleaned_line: str, title: str) -> bool:
    if not cleaned_line:
        return True

    cleaned_lower = cleaned_line.lower()
    title_lower = clean_description_text(title).lower()

    if cleaned_lower == title_lower:
        return True
    if cleaned_lower in {word.lower() for word in SUBJECT_WORDS}:
        return True
    if re.fullmatch(
        r"(pr[aá]ctica|practica|proyecto|project)\s*#?\s*\d+",
        cleaned_lower,
        flags=re.IGNORECASE,
    ):
        return True

    return False


def extract_description(text: str, title: str) -> str:
    in_code_block = False
    paragraph: list[str] = []

    for raw_line in text.splitlines():
        line = raw_line.strip()

        if line.startswith("```"):
            in_code_block = not in_code_block
            continue
        if in_code_block:
            continue
        if not line:
            if paragraph:
                break
            continue
        if line.startswith("#"):
            continue
        if line.startswith("<!--"):
            continue
        if line.startswith("!"):
            continue
        if line.startswith("|"):
            continue
        if re.match(r"^[-:| ]+$", line):
            continue

        cleaned = clean_description_text(strip_markdown(line))
        if should_skip_description_line(cleaned, title):
            continue

        paragraph.append(cleaned)

    if not paragraph:
        return "README local del trabajo."

    description = normalize_spaces(" ".join(paragraph))
    return description[:157].rstrip() + "..." if len(description) > 160 else description


def extract_tags(text: str) -> str:
    found: list[str] = []
    lower_text = text.lower()
    for needle, label in KEYWORDS:
        if needle.lower() in lower_text and label not in found:
            found.append(label)
    return ", ".join(found[:5]) if found else "—"


def item_sort_key(path: Path) -> tuple[int, int, str]:
    label, number = extract_item_metadata(path)
    type_order = 1 if label == "Proyecto" else 0
    return type_order, number if number is not None else 10_000, path.relative_to(ROOT).as_posix().lower()


def iter_nested_readmes() -> list[Path]:
    readmes: list[Path] = []
    for path in ROOT.rglob("README.md"):
        rel = path.relative_to(ROOT)
        if rel == Path("README.md"):
            continue
        parts = {part.lower() for part in rel.parts[:-1]}
        if parts & IGNORED_DIRS:
            continue
        readmes.append(path)
    return sorted(readmes, key=item_sort_key)


def build_generated_section() -> str:
    readmes = iter_nested_readmes()
    if not readmes:
        return "\n_Aún no se encontraron README.md dentro de carpetas de prácticas o proyectos._\n"

    lines = [
        "",
        "<!-- Esta tabla se genera automáticamente con scripts/update_main_readme.py. -->",
        f"**Total de trabajos documentados:** {len(readmes)}",
        "",
        "| Trabajo | Resumen | Temas detectados |",
        "|---|---|---|",
    ]

    for readme_path in readmes:
        text = readme_path.read_text(encoding="utf-8", errors="ignore")
        title = extract_title(readme_path, text)
        item_title = format_item_title(readme_path, title, text)
        description = extract_description(text, title)
        tags = extract_tags(text)
        rel_path = readme_path.relative_to(ROOT).as_posix()
        link = quote(rel_path, safe="/#")
        lines.append(
            f"| [{escape_table_cell(item_title)}]({link}) | "
            f"{escape_table_cell(description)} | {escape_table_cell(tags)} |"
        )

    lines.append("")
    return "\n".join(lines)


def default_readme() -> str:
    return f"""# Microprocesadores

Repositorio de prácticas y proyectos de la materia **Microprocesadores**.

Los proyectos están orientados al uso del **PIC16F887**, desarrollados con **MPLAB X IDE / XC8** y simulados en **Proteus** cuando aplica.

## Índice de prácticas y proyectos

{START_MARKER}
{END_MARKER}

## Cómo agregar una nueva práctica o proyecto

1. Crea una carpeta para el trabajo.
2. Agrega un `README.md` local dentro de esa carpeta.
3. Escribe un título con `#` o `<h1>` y una descripción breve al inicio del README local.
4. Indica `Práctica #N` o `Proyecto #N` en el encabezado o en el nombre de la carpeta.
5. Sube los cambios al repositorio.

El índice principal se actualiza automáticamente con GitHub Actions.

## Estructura sugerida para cada trabajo

```text
Practica-XX-Nombre/
├── README.md
├── src/
├── proteus/
└── docs/
```

## Herramientas

- Microcontrolador: PIC16F887
- IDE: MPLAB X IDE
- Compilador: XC8
- Simulación: Proteus
"""


def update_main_readme() -> bool:
    current = MAIN_README.read_text(encoding="utf-8") if MAIN_README.exists() else default_readme()
    generated = build_generated_section()

    if START_MARKER not in current or END_MARKER not in current:
        current = current.rstrip() + f"\n\n## Índice de prácticas y proyectos\n\n{START_MARKER}\n{END_MARKER}\n"

    current = current.replace("## Índice de prácticas\n", "## Índice de prácticas y proyectos\n")
    current = current.replace(
        "Repositorio de prácticas de la materia **Microprocesadores**.",
        "Repositorio de prácticas y proyectos de la materia **Microprocesadores**.",
    )

    pattern = re.compile(
        re.escape(START_MARKER) + r".*?" + re.escape(END_MARKER),
        flags=re.DOTALL,
    )
    replacement = f"{START_MARKER}{generated}{END_MARKER}"
    updated = pattern.sub(replacement, current)

    if updated != current:
        MAIN_README.write_text(updated, encoding="utf-8")
        return True
    return False


if __name__ == "__main__":
    changed = update_main_readme()
    print("README.md updated." if changed else "README.md already up to date.")

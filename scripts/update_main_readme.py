#!/usr/bin/env python3
"""Update the main README.md from every nested README.md in the repo.

The script scans the repository for README.md files inside practice folders and
rebuilds only the block delimited by AUTO-GENERATED-PRACTICES markers.
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


def first_number_match(pattern: str, source: str) -> int | None:
    match = re.search(pattern, source, flags=re.IGNORECASE)
    if not match:
        return None

    for group in match.groups():
        if group and group.isdigit():
            return int(group)
    return None


def extract_practice_number(readme_path: Path, text: str = "") -> int | None:
    rel = readme_path.relative_to(ROOT).as_posix()
    sources = [text, rel]
    patterns = [
        r"pr[aá]ctica\s*#?\s*(\d+)",
        r"practica\s*#?\s*(\d+)",
        r"pr[aá]ctica[ _.-]*(\d+)",
        r"practica[ _.-]*(\d+)",
        r"(?:^|/)(?:p|prac)[ _.-]*(\d+)",
        r"(?:^|/)(\d+)(?:[^0-9]|$)",
    ]

    for source in sources:
        for pattern in patterns:
            number = first_number_match(pattern, source)
            if number is not None:
                return number
    return None


def format_practice_title(readme_path: Path, title: str, text: str) -> str:
    number = extract_practice_number(readme_path, text)
    title = clean_description_text(title)
    title = re.sub(r"\bpr[aá]ctica\s*#?\s*\d+\b", "", title, flags=re.IGNORECASE)
    title = re.sub(r"\bpractica\s*#?\s*\d+\b", "", title, flags=re.IGNORECASE)
    title = normalize_spaces(title).upper()

    if number is None:
        return title
    return f"Práctica #{number} - {title}"


def should_skip_description_line(cleaned_line: str, title: str) -> bool:
    if not cleaned_line:
        return True

    cleaned_lower = cleaned_line.lower()
    title_lower = clean_description_text(title).lower()

    if cleaned_lower == title_lower:
        return True
    if cleaned_lower in {word.lower() for word in SUBJECT_WORDS}:
        return True
    if re.fullmatch(r"pr[aá]ctica\s*#?\s*\d+", cleaned_lower, flags=re.IGNORECASE):
        return True
    if re.fullmatch(r"practica\s*#?\s*\d+", cleaned_lower, flags=re.IGNORECASE):
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
        return "README local de la práctica."

    description = normalize_spaces(" ".join(paragraph))
    return description[:157].rstrip() + "..." if len(description) > 160 else description


def extract_tags(text: str) -> str:
    found: list[str] = []
    lower_text = text.lower()
    for needle, label in KEYWORDS:
        if needle.lower() in lower_text and label not in found:
            found.append(label)
    return ", ".join(found[:5]) if found else "—"


def practice_sort_key(path: Path) -> tuple[int, str]:
    number = extract_practice_number(path)
    return number if number is not None else 10_000, path.relative_to(ROOT).as_posix().lower()


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
    return sorted(readmes, key=practice_sort_key)


def build_generated_section() -> str:
    readmes = iter_nested_readmes()
    if not readmes:
        return "\n_Aún no se encontraron README.md dentro de carpetas de prácticas._\n"

    lines = [
        "",
        "<!-- Esta tabla se genera automáticamente con scripts/update_main_readme.py. -->",
        f"**Total de prácticas documentadas:** {len(readmes)}",
        "",
        "| Práctica | Resumen | Temas detectados |",
        "|---|---|---|",
    ]

    for readme_path in readmes:
        text = readme_path.read_text(encoding="utf-8", errors="ignore")
        title = extract_title(readme_path, text)
        practice_title = format_practice_title(readme_path, title, text)
        description = extract_description(text, title)
        tags = extract_tags(text)
        rel_path = readme_path.relative_to(ROOT).as_posix()
        link = quote(rel_path, safe="/#")
        lines.append(
            f"| [{escape_table_cell(practice_title)}]({link}) | "
            f"{escape_table_cell(description)} | {escape_table_cell(tags)} |"
        )

    lines.append("")
    return "\n".join(lines)


def default_readme() -> str:
    return f"""# Microprocesadores

Repositorio de prácticas de la materia **Microprocesadores**.

Los proyectos están orientados al uso del **PIC16F887**, desarrollados con **MPLAB X IDE / XC8** y simulados en **Proteus** cuando aplica.

## Índice de prácticas

{START_MARKER}
{END_MARKER}

## Cómo agregar una nueva práctica

1. Crea una carpeta para la práctica.
2. Agrega un `README.md` local dentro de esa carpeta.
3. Escribe un título con `#` y una descripción breve al inicio del README local.
4. Sube los cambios al repositorio.

El índice principal se actualiza automáticamente con GitHub Actions.

## Estructura sugerida para cada práctica

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
        current = current.rstrip() + f"\n\n## Índice de prácticas\n\n{START_MARKER}\n{END_MARKER}\n"

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

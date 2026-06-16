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


def humanize_folder_name(path: Path) -> str:
    name = path.parent.name.replace("_", " ").replace("-", " ")
    return normalize_spaces(name).title() or path.parent.as_posix()


def extract_title(readme_path: Path, text: str) -> str:
    for line in text.splitlines():
        match = re.match(r"^#\s+(.+)$", line.strip())
        if match:
            title = strip_markdown(match.group(1))
            if title:
                return title
    return humanize_folder_name(readme_path)


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

        cleaned = strip_markdown(line)
        if cleaned and cleaned.lower() != title.lower():
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
    rel = path.relative_to(ROOT).as_posix().lower()
    number_match = re.search(r"(?:pr[aá]ctica|practica|prac|p)[ _.-]*(\d+)", rel)
    if not number_match:
        number_match = re.search(r"(^|/)(\d+)([^0-9]|$)", rel)
    number = int(number_match.group(1 if number_match.lastindex == 1 else 2)) if number_match else 10_000
    return number, rel


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
        "| # | Práctica | Resumen | Temas detectados |",
        "|---:|---|---|---|",
    ]

    for index, readme_path in enumerate(readmes, start=1):
        text = readme_path.read_text(encoding="utf-8", errors="ignore")
        title = extract_title(readme_path, text)
        description = extract_description(text, title)
        tags = extract_tags(text)
        rel_path = readme_path.relative_to(ROOT).as_posix()
        link = quote(rel_path, safe="/#")
        lines.append(f"| {index} | [{title}]({link}) | {description} | {tags} |")

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

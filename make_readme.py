import os
import subprocess
if os.name == 'nt':
    os.add_dll_directory(r"C:\Program Files (x86)\WinFsp\bin")
import rman_py

# Configuration: Map Python functions to their CLI executable counterparts
TOOLS = {
    "bundle": {
        "check": "rbun-chk",
        "extract": "rbun-ex",
        "list": "rbun-ls",
        "merge": "rbun-merge",
        "usage": "rbun-usage",
    },
    "manifest": {
        "list_bundles": "rman-bl",
        "check": "rman-chk",
        "diff": "rman-diff",
        "download": "rman-dl",
        "list": "rman-ls",
        "make": "rman-make",
        "merge": "rman-merge",
        "mount": "rman-mount",
        "rads": "rman-rads",
        "remake": "rman-remake",
    }
}

# Adjust this path if your binaries are elsewhere
BIN_DIR = os.path.abspath("./build/Release")

def get_signature(func_obj):
    """Extracts signature from docstring (pybind11 standard)."""
    doc = func_obj.__doc__
    if not doc:
        return "(...)"

    # pybind11 usually puts the signature on the first line
    # e.g. "check(inputs: list[str], no_hash: bool = False) -> None"
    first_line = doc.split('\n')[0].strip()

    # If the first line contains the function name, strip it to get just the parens
    if "(" in first_line:
        return first_line[first_line.find("("):]
    return "(...)"

def get_cli_help(bin_name):
    """Runs the .exe and captures --help output."""
    exe_path = os.path.join(BIN_DIR, f"{bin_name}.exe")
    if not os.path.exists(exe_path):
        return f"Warning: {bin_name}.exe not found in {BIN_DIR}"
    try:
        result = subprocess.run([exe_path, "--help"], capture_output=True, text=True)
        # Handle cases where output might be in stderr or stdout
        help_text = result.stdout.strip() or result.stderr.strip()
        return help_text
    except Exception as e:
        return f"Error running {bin_name}: {e}"

def generate():
    try:
        with open("examples.py", "r", encoding="utf-8") as f:
            example_content = f.read()
    except FileNotFoundError:
        example_content = "# examples.py not found"

    # 2. Build the Header
    lines = [
        "# rman_py",
        "Python bindings for the Riot Manifest and Bundle toolkit.",
        "",
        "## Installation",
        "```sh",
        "pip install .",
        "```",
        "",
        "## Usage Examples",
        "Below are examples of basic usage for all available functions.",
        "```python",
        example_content.strip(),
        "```",
        "",
        "## API Reference",
        "Detailed parameter list for each function. Python argument names match original CLI flags using `snake_case`.",
        ""
    ]

    for sub_name, funcs in TOOLS.items():
        lines.append(f"## Module: `rman_py.{sub_name}`")
        lines.append("")

        # Check if submodule exists
        if not hasattr(rman_py, sub_name):
            print(f"Warning: Submodule rman_py.{sub_name} not found.")
            continue

        submodule = getattr(rman_py, sub_name)

        for py_func_name, bin_name in funcs.items():
            if not hasattr(submodule, py_func_name):
                print(f"Warning: Function {py_func_name} not found in {sub_name}.")
                continue

            lines.append(f"### `{sub_name}.{py_func_name}`")

            # 1. Get the Python Signature from docstring
            func_obj = getattr(submodule, py_func_name)
            sig = get_signature(func_obj)
            lines.append("**Python Usage:**")
            lines.append(f"```python\nrman_py.{sub_name}.{py_func_name}{sig}\n```")

            # 2. Get the CLI Help
            lines.append("**Description & CLI Arguments:**")
            cli_help = get_cli_help(bin_name)
            lines.append(f"```text\n{cli_help}\n```")
            lines.append("")
            lines.append("---")
            lines.append("")

    with open("README.md", "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

    print("Successfully generated README.md")

if __name__ == "__main__":
    generate()
#!/usr/bin/env python3
import sys
import re
import os

def embed_include(src_path, header_path, include_pattern, out_path):
    with open(src_path, "r") as f:
        src = f.read()

    with open(header_path, "r") as f:
        header_content = f.read()

    pattern = re.compile(r'^\s*#include\s*[<"]' + re.escape(include_pattern) + r'[>"]\s*$', re.MULTILINE)

    if not pattern.search(src):
        print(f"Warning: no include of '{include_pattern}' found in {src_path}")
        sys.exit(1)

    wrapped = (
        f"/* ===== begin embedded {include_pattern} ===== */\n"
        f"{header_content}\n"
        f"/* ===== end embedded {include_pattern} ===== */"
    )

    result = pattern.sub(lambda m: wrapped, src, count=1)

    out_dir = os.path.dirname(out_path)
    if out_dir:
        os.makedirs(out_dir, exist_ok=True)

    with open(out_path, "w") as f:
        f.write(result)

    print(f"Embedded {header_path} into {out_path}")

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: embed.py <source_file> <header_to_embed> <include_name> <output_file>")
        print("Example: embed.py mylib.h stb_image.h stb_image.h dist/mylib_dist.h")
        sys.exit(1)

    embed_include(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
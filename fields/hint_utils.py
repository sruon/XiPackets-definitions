"""Utilities for extracting hints from cursor comments"""

import re
from typing import Optional, Dict, Any


def extract_hints(cursor) -> Optional[Dict[str, Any]]:
    """Extract structured hints from cursor comments"""
    if not cursor.location.file:
        return {}
    try:
        with open(cursor.location.file.name, 'r') as f:
            line = f.readlines()[cursor.location.line - 1]
        if '//' not in line:
            return {}
        
        comment = line.split('//')[1].strip()
        hints = {}
        for match in re.finditer(r'(\w+)="([^"]+)"', comment):
            key, value = match.group(1), match.group(2)
            if key in hints:
                if not isinstance(hints[key], list):
                    hints[key] = [hints[key]]
                hints[key].append(value)
            else:
                hints[key] = value
        return hints
    except:
        return {}
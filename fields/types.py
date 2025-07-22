"""Core type definitions for fields module"""

from dataclasses import dataclass
from typing import Optional, List


@dataclass
class UnionVariant:
    """Represents a single variant in a union"""
    name: str
    discriminator_value: Optional[int]
    fields: List['StructField']  # Forward reference
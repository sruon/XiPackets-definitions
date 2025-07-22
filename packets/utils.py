"""Utilities for packet parsing"""

from .exceptions import PacketParsingError


def extract_packet_id(cursor):
    """Extract packet ID from cursor comment"""
    if cursor.brief_comment:
        return cursor.brief_comment.rstrip()
    raise PacketParsingError("No ID comment found on packet")
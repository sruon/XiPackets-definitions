from clang import cindex as clang

from fields import StructField


class Packet:
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.fields = []
        self.id = self._extract_id(cursor)

        for field in cursor.get_children():
            if field.kind == clang.CursorKind.FIELD_DECL:
                self.fields.append(StructField(field))
            elif field.kind == clang.CursorKind.UNION_DECL:
                self.fields.append(StructField(field))

    def __repr__(self):
        return f"{self.name} (id={self.id}, ({len(self.fields)} fields))"

    def _extract_id(self, cursor):
        if cursor.brief_comment:
            return cursor.brief_comment.rstrip()
        raise Exception(f"{self.name} has no ID comment")

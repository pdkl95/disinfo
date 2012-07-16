#ifndef INDENT_H
#define INDENT_H

#define ENVNAME_ADD_INDENT "DISINFO_INDENT_MORE"

#define INDENT_STRING "  "
#define INDENT_WIDTH sizeof (INDENT_STRING)
#define INDENT_MAX 40

int get_indent(void);
int dindent(void);
int doutdent(void);


#endif /*INDENT_H*/

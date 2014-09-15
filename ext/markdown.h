#ifndef _MARKDOWN_D
#define _MARKDOWN_D

#include "cstring.h"

/* reference-style links (and images) are stored in an array
 * of footnotes.
 */
typedef struct footnote {
    Cstring tag;		/* the tag for the reference link */
    Cstring link;		/* what this footnote points to */
    Cstring title;		/* what it's called (TITLE= attribute) */
    int height, width;		/* dimensions (for image link) */
} Footnote;

/* each input line is read into a Line, which contains the line,
 * the offset of the first non-space character [this assumes
 * that all tabs will be expanded to spaces!], and a pointer to
 * the next line.
 */
typedef struct line {
    Cstring text;
    struct line *next;
    int dle;
} Line;


/* a paragraph is a collection of Lines, with links to the next paragraph
 * and (if it's a QUOTE, UL, or OL) to the reparsed contents of this
 * paragraph.
 */
typedef struct paragraph {
    struct paragraph *next;	/* next paragraph */
    struct paragraph *down;	/* recompiled contents of this paragraph */
    struct line *text;		/* all the text in this paragraph */
    char *ident;		/* %id% tag for QUOTE */
    enum { WHITESPACE=0, CODE, QUOTE, MARKUP,
	   HTML, STYLE, DL, UL, OL, AL, LISTITEM,
	   HDR, HR } typ;
    enum { IMPLICIT=0, PARA, CENTER} align;
    int hnumber;		/* <Hn> for typ == HDR */
} Paragraph;

enum { ETX, SETEXT };	/* header types */


typedef struct block {
    enum { bTEXT, bSTAR, bUNDER } b_type;
    int  b_count;
    char b_char;
    Cstring b_text;
    Cstring b_post;
} block;

typedef STRING(block) Qblock;


/* a magic markdown io thing holds all the data structures needed to
 * do the backend processing of a markdown document
 */
typedef struct mmiot {
    Cstring out;
    Cstring in;
    Qblock Q;
    int isp;
    STRING(Footnote) *footnotes;
    int flags;
#define DENY_A		0x0001
#define DENY_IMG	0x0002
#define DENY_SMARTY	0x0004
#define DENY_HTML	0x0008
#define STRICT		0x0010
#define INSIDE_TAG	0x0020
#define NO_PSEUDO_PROTO	0x0040
#define CDATA_OUTPUT	0x0080
#define TOC		0x1000
#define MKD_1_COMPAT	0x2000
#define USER_FLAGS	0xF0FF
#define EMBEDDED	DENY_A|DENY_IMG|NO_PSEUDO_PROTO|CDATA_OUTPUT
    char *base;
} MMIOT;


/*
 * the mkdio text input functions return a document structure,
 * which contains a header (retrieved from the document if
 * markdown was configured * with the * --enable-pandoc-header
 * and the document begins with a pandoc-style header) and the
 * root of the linked list of Lines.
 */
typedef struct document {
    Line *headers;		/* title -> author(s) -> date */
    ANCHOR(Line) content;	/* uncompiled text, not valid after compile() */
    Paragraph *code;		/* intermediate code generated by compile() */
    int compiled;		/* set after mkd_compile() */
    int html;			/* set after (internal) htmlify() */
    int tabstop;		/* for properly expanding tabs (ick) */
    MMIOT *ctx;			/* backend buffers, flags, and structures */
    char *base;			/* url basename for url fragments */
} Document;


extern int  mkd_firstnonblank(Line *);
extern int  mkd_compile(Document *, int);
extern int  mkd_document(Document *, char **);
extern int  mkd_generatehtml(Document *, FILE *);
extern int  mkd_style(Document *, FILE *);
extern void mkd_cleanup(Document *);
extern int  mkd_text(char *, int, FILE*, int);
extern void mkd_basename(Document*, char *);
extern void mkd_string_to_anchor(char*,int, void(*)(int,void*), void*);

extern Document *mkd_in(FILE *, int);
extern Document *mkd_string(char*,int, int);

#define NO_HEADER	0x0100
#define STD_TABSTOP	0x0200
#define INPUT_MASK	(NO_HEADER|STD_TABSTOP)


/* internal resource handling functions.
 */
extern void ___mkd_freeLine(Line *);
extern void ___mkd_freeLines(Line *);
extern void ___mkd_freeParagraph(Paragraph *);
extern void ___mkd_freefootnotes(MMIOT *);
extern void ___mkd_initmmiot(MMIOT *, void *);
extern void ___mkd_freemmiot(MMIOT *, void *);
extern void ___mkd_freeLineRange(Line *, Line *);
extern void ___mkd_xml(char *, int, FILE *);
extern void ___mkd_reparse(char *, int, int, MMIOT*);
extern void ___mkd_emblock(MMIOT*);
extern void ___mkd_tidy(Line *);

#endif/*_MARKDOWN_D*/

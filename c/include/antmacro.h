#ifndef ANTMACRO_H
#define ANTMACRO_H

#define ENDL "\n"

#define ANSI_RED "\033[31;1;4m"
#define ANSI_BLUE "\033[34;1;1m"
#define ANSI_YELLOW "\033[33;1;1m"
#define ANSI_GREEN "\033[92;1;1m"
#define ANSI_END "\033[0m"

#define ERROR(tok) ANSI_RED tok ANSI_END
#define TRACE(tok) ANSI_BLUE tok ANSI_END
#define DEBUG(tok) ANSI_YELLOW tok ANSI_END
#define IO_OK(tok) ANSI_GREEN tok ANSI_END

#define ERRORLN(tok) ERROR(tok) ENDL
#define TRACELN(tok) TRACE(tok) ENDL
#define DEBUGLN(tok) DEBUG(tok) ENDL
#define IO_OKLN(tok) IO_OK(tok) ENDL

#ifdef LIBANT_DEBUG
#define set_name(obj, id) obj->__debug_head.name = id
#define nameof(obj) obj->__debug_head.name

typedef struct __debug_head __debug_head;

struct __debug_head
{

	char * name;

};

#define IF_DEBUG(x) x
#else
#define IF_DEBUG(x)
#endif

#define LOG(x) IF_DEBUG(x) // for readability

#define str(x) #x
#define xstr(x) str(x)

#define lb_container_of(ptr, type, member) ((type *) ((char *)(ptr) - offsetof(type, member)))

#endif

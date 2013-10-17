# gdb implementation of the /proc/modules file
define lsmod
    set $current = modules.next
    set $offset =  ((int)&((struct module *)0).list)
    printf "Module\tAddress\n"

    while($current.next != modules.next)
        printf "%s\t%p\n",  \
        ((struct module *) (((void *) ($current)) - $offset ) )->name ,\
        ((struct module *) (((void *) ($current)) - $offset ) )->module_core
        set $current = $current.next
    end
end

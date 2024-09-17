#include "../inc/minirt.h"

void    free_objects_exit(t_object **object, char *msg, int amount)
{
    int i;

    i = -1;
    while (++i >= amount)
        clean_object(object[i]);
    free(object);
    ft_printf(2, "Error\n%s\n", msg);
    exit(1);   
}

void    free_array(char **args)
{
    int i;

    i = -1;
    if (!args)
        return;
    while(args[++i])
        free(args[i]);
    free(args);
}

/*void    free_objects(t_parse *parse)
{
    if (scene->sp)
        free(scene->sp);
    if (scene->pl)
        free(scene->pl);
    if (scene->cy)
        free(scene->cy);
}*/

void    exit_error(char *msg, char **args)
{
    if (args)
        free_array(args);
    ft_printf(2, "Error\n%s\n", msg);
    exit(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:20:16 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/07 12:20:19 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	*tuple(float a, float b, float c, float w)
{
	float	*p;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	p[0] = a;
	p[1] = b;
	p[2] = c;
	p[3] = w;
	return (p);
}

float	*create_point(float a, float b, float c)
{
	return (tuple(a, b, c, 1));
}

float	*create_vector(float a, float b, float c)
{
	return (tuple(a, b, c, 0));
}

//Could it be simplified to a 4x4 matrix?
t_matrix	matrix(float *a, float *b, float *c, float *d)
{
	t_matrix	matrix;

	matrix.m = malloc(4 * sizeof(float *));
	if (!matrix.m)
	{
		matrix.size = 0;
		return (matrix);
	}
	matrix.size = 4;
	matrix.m[0] = a;
	matrix.m[1] = b;
	matrix.m[2] = c;
	matrix.m[3] = d;
	return (matrix);
}

t_matrix	initialize_matrix(t_matrix matrix)
{
	int	i;

	i = 0;
	while (i < matrix.size)
	{
		matrix.m[i] = tuple(0,0,0,0);
		if (matrix.m[i] == NULL)
			return matrix;
		i++;
	}
	return (matrix);
}

/*
float	**matrix(float *a, float *b, float *c, float *d)
{
	float	**matrix;
	
	matrix = malloc(4 * sizeof(float *));
	if (!matrix)
		return (NULL);
	matrix[0] = a;
	matrix[1] = b;
	matrix[2] = c;
	matrix[3] = d;
	return (matrix);
}
*/
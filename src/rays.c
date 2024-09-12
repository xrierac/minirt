/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:46:54 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/12 10:25:17 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	**transform_ray(float **ray, t_matrix *matrix)
{
	float		**trans;
	float		*p;
	float		*v;
	//t_matrix	*inv;
	
	//Should we build the inverse here????
	//inv = inverse_matrix(matrix);
	//if (!inv)
	//	return (NULL);
	p = four_one_multiply(matrix, ray[0]);
	if (!p)
		return (NULL);
	v = four_one_multiply(matrix, ray[1]);
	if (!v)
	{
		free(p);
		return (NULL);
	}
	trans = create_ray(p, v);
	if (!trans)
	{
		free(v);
		free(p);
		return (NULL);
	}
	//clean_matrix(inv, 4);
	return (trans);
}

float	**create_ray(float *origin, float *direction)
{
	float	**r;

	if (origin[3] == 0 || direction[3] == 1)
	{
		printf("Error: Wrong ray input\n");
		return (NULL);
	}
	r = malloc(2 * sizeof(float *));
	if (!r)
		return (NULL);
	r[0] = origin;
	r[1] = direction;
	return (r);
}

float	*ray_position(float **r, float t)
{
	float	*p;
	int		i;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 3)
	{	
		p[i] = r[0][i] + r[1][i] * t;
		i++;
	}
	p[i] = 1;
	return (p);
}

static	float	**ray_pixel_help(t_matrix *inv, float x, float y)
{
	float	*pixel;
	float	*origin;
	float	*p1;
	float	*p2;

	p1 = create_point(x, y, -1);
	p2 = create_point(0, 0, 0);
	if (p1 && p2)
	{
		pixel = four_one_multiply(inv, p1);
		origin = four_one_multiply(inv, p2);
		free(p1);
		free(p2);
		if (pixel && origin)
		{
			p1 = tuple_subs(pixel, origin);
			if (p1)
				p2 = normalize(p1);
			free(pixel);
			free(p1);
			return (create_ray(origin, p2));
		}
	clean_points(p1, p2, pixel, origin);
	}
	return (NULL);
}

float	**ray_for_pixel(t_camera *c, float px, float py)
{
	float		x;
	float		y;
	float		**ray;
	//t_matrix	*inv;

	//inv = inverse_matrix(c->transform);
	//if (!inv)
	//	return (NULL);
	x = (px + 0.5) * c->pixel_size;
	y = (py + 0.5) * c->pixel_size;
	x = c->half_width - x;
	y = c->half_height - y;
	ray = ray_pixel_help(c->transform, x, y);
	//clean_matrix(inv, 4);
	return (ray);
}
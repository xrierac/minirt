/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:12:35 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/18 18:22:38 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_pattern	*create_pattern(float *a, float *b, t_matrix *transf)
{
	t_pattern	*pat;

	pat = malloc(sizeof(t_pattern));
	if (!pat)
		return (NULL);
	pat->colora = a;
	pat->colorb = b;
	pat->transf = transf;
	return (pat);
}

static float	*checkers(t_pattern *pattern, float *p)
{
	if (fmod(floor(p[0]) + floor(p[1]) + floor(p[2]), 2) == 0)
		return (pattern->colora);
	return (pattern->colorb);
}

static float *sphere_checkers(t_pattern *pattern, float *p)
{
    float	u;
    float	v;
    float	theta; 
	float	phi;
	
	theta = atan2(p[2], p[0]);
	phi = acos(p[1] / sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]));
	u = (theta + PI) / (2 * PI);
	v = phi / PI;
	if (fmod((floor(u * 100) + floor(v * 50)), 2) == 0)
    	return (pattern->colora);
    return (pattern->colorb);
}

static float *cylinder_checkers(t_pattern *pattern, float *p)
{
    float u, v;
    float theta;
    int check_u, check_v;

    // Calculate theta (angle around the cylinder axis)
    theta = atan2(p[2], p[0]);

    // Map coordinates
    u = (theta + PI) / (2 * PI);  // u represents the angle around the cylinder
    //v = fmod(p[1], 1.0);          // v represents the height along the cylinder axis
	v = 0;
    // Ensure v is positive
    if (v < 0) v += 1.0;

    // Scale UV coordinates to create checker pattern
    check_u = floor(u * 8);  // Adjust for number of checks around the cylinder
    check_v = floor(v * 8);  // Adjust for number of checks along the height

    //if (fmod((floor(u * 8) + floor(v * 8)), 2) == 0)
    if ((check_u + check_v) % 2 == 0)
        return (pattern->colora);
    return (pattern->colorb);
}

float	*checker_at_obj(t_comp *comp)
{
	float	*objp;
	float	*pattp;

	objp = four_one_multiply(comp->object->transform, comp->over_point, 0);
	if (!objp)
		return (NULL);
	pattp = four_one_multiply(comp->object->material->patt->transf, objp, 1);
	if (!pattp)
		return (NULL);
    if (comp->object->s == SPHERE)
        return (sphere_checkers(comp->object->material->patt, pattp));
    if (comp->object->s == CYLINDER)
	    return (cylinder_checkers(comp->object->material->patt, pattp));
    return (checkers(comp->object->material->patt, pattp));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:47:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/15 14:44:59 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static t_camera	*compute_pixel_size(t_camera *camera)
{
	float	half_view;
	float	aspect;

	half_view = tan(camera->field / 2);
	aspect = camera->hsize / camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	return (camera);
}

t_camera	*create_camera(float hsize, float vsize, float field)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->transform = create_identity(4);
	if (!camera->transform)
	{
		free(camera);
		return (NULL);
	}
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->field = field;
	return (compute_pixel_size(camera));
}

int	render(t_camera *camera, t_world *world)
{
	int	x;
	int	y;
	float	**ray;
	float	*col;

	mlx_t* mlx = mlx_init(camera->hsize, camera->vsize, "MLX42", true);
	if (!mlx)
		exit(1);
	mlx_image_t* img = mlx_new_image(mlx, camera->hsize, camera->vsize);
	mlx_image_to_window(mlx, img, 0, 0);
	y = 0;
	while (y < camera->vsize)
	{
		x = 0;
		while (x < camera->hsize)
		{
			ray = ray_for_pixel(camera, x, y);
			col = color_at(world, ray);
			mlx_put_pixel(img, x, y, colors_to_int(conv_color_back(col),256));
			clean_ray(ray);
			free(col);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
    mlx_terminate(mlx);
	return (1);
}
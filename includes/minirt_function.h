/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_function.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:31:14 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 19:26:30 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FUNCTION_H
# define MINIRT_FUNCTION_H

# include "minirt_structure.h"

// Exit Hooks
// int			minirt_close(t_minirt *minirt);
int			minirt_close(int keycode, t_minirt *minirt);
int			minirt_esc(int keycode, t_minirt *minirt);
int			camera_move(int keycode, t_minirt *minirt);
int			camera_zoom(int keycode, int x, int y, t_minirt *minirt);

// Output & Display Color per Pixel
void		minirt_pixel_put(t_img_data *data, int x, int y, int color);
void		minirt_pixel_put_vector(t_img_data *data, int x, int y, t_color color);
t_color		write_color(int fd, t_color	color);

void		canvas_init(t_minirt *minirt, int width, int height);

void		camera_init(t_minirt *minirt, t_canvas *canvas, t_point3 origin);

// Vector
t_vec3		vector_init(double x, double y, double z);
t_point3	point_init(double x, double y, double z);
t_color		color_init(double r, double g, double b);

// Vector Operation
double		vlength(t_vec3 v);
double		vlength2(t_vec3 v);
t_vec3		vsum(t_vec3 u, t_vec3 v);
t_vec3		vsub(t_vec3 u, t_vec3 v);
t_vec3		vmul(t_vec3 u, t_vec3 v);
t_vec3		vmul_t(double t, t_vec3 v);
t_vec3		vdiv(t_vec3 v, double t);
double		vdot(t_vec3 u, t_vec3 v);
t_vec3		vcross(t_vec3 u, t_vec3 v);
t_vec3		vunit(t_vec3 v);

// Ray
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	ray_at(t_ray *r, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
// t_color 	ray_color(t_sphere *sp, t_ray *r);
// t_color 	ray_color(int type, void *obj, t_ray *r);
t_color 	ray_color(t_object *world, t_ray *r);

void    	set_face_normal(t_ray *r, t_hit_record *rec);


// Object
t_object	*object_init(t_object_type type, void *element, t_color color);
void		object_add(t_object **list, t_object *new);
t_object	*object_last(t_object *list);
void		object_clear(t_object **list);

// Determining Hittable Object
t_bool		hit(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool		hit_object(t_object *world, t_ray *ray, t_hit_record *rec);

// Sphere
t_sphere	*sphere_init(t_point3 center, double radius);
int			hit_sphere(t_object *sphere, t_ray *r, t_hit_record *rec);

// Plane
t_plane		*plane_init(t_point3 orig, t_vec3 normal);
t_bool		hit_plane(t_object *world, t_ray *r, t_hit_record *rec);
t_bool	intersect_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);

// Cylinder
t_cylinder	*cylinder_init(t_point3 orig, t_vec3 normal);
t_bool		hit_cylinder(t_object *world, t_ray *r, t_hit_record *rec);

// Square
t_square	*square_init(t_point3 center, t_vec3 normal, double side_len);
t_bool		hit_square(t_object *world, t_ray *ray, t_hit_record *rec);

// Concept
void		minirt_background(t_img_data *data, int width, int height, t_vec3 color);
void		minirt_gradation(t_minirt *minirt);
void		minirt_sky(t_minirt	*minirt);
void		minirt_world(t_minirt *minirt);
void		minirt_plane_in_the_sky(t_minirt *minirt);

void		minirt_free(void *data);

#endif
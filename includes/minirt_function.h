/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_function.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:31:14 by bahn              #+#    #+#             */
/*   Updated: 2022/05/09 20:25:17 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FUNCTION_H
# define MINIRT_FUNCTION_H

# include "minirt.h"

void		output_scene(t_scene *scene);

// Exit Hooks
int			minirt_close(t_scene *scene);
int			minirt_esc(int keycode, t_scene *scene);
int			camera_move(int keycode, t_scene *scene);
int			camera_zoom(int keycode, int x, int y, t_scene *scene);
int			camera_switch(t_scene *scene);

// Output & Display Color per Pixel
void		minirt_pixel_put(t_img_data *data, int x, int y, int color);
void		minirt_pixel_put_vector(t_img_data *data,	\
				int x, int y, t_color3 color);
t_color3	write_color(t_color3 color);
t_color3	skyview_by_ray(t_ray *ray);

// Canvas
void		init_canvas(t_scene *scene, int width, int height);

// Camera
void		init_camera(t_scene *scene);
void		set_camera(t_camera *camera, double aspect_ratio);
void		print_caminfo(t_camera *cam);

// Vector
t_vec3		vector_init(double x, double y, double z);
t_point3	point_init(double x, double y, double z);
t_color3	color_init(double r, double g, double b);

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
t_vec3		vmin(t_vec3 u, t_vec3 v);

// Ray
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	ray_at(t_ray *r, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);

void		set_face_normal(t_ray *r, t_hit_record *rec);

// Object
t_object	*object_init(t_object_type type, void *element, t_color3 color);
void		object_add(t_object **list, t_object *new);
t_object	*object_last(t_object *list);
void		object_clear(t_object **list);

// Determining Hittable Object
t_bool		hit(t_object *objects, t_ray *ray, t_hit_record *rec);
t_bool		hit_object(t_object *objects, t_ray *ray, t_hit_record *rec);
t_bool		hit_shadow(t_object *objects, t_ray *ray, double limit);

// Light
t_light		*light_init(t_point3 light_origin, t_color3 light_color,
				double bright_ratio);
t_color3	phong_lighting(t_scene *scene);
t_color3	get_point_light(t_scene *scene, t_light *light);
t_color3	diffuse_calculator(t_vec3 light_dir, t_color3 light_color,
				t_vec3 rec_normal);
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_color3	specular_calculator(t_vec3 ray_dir, t_vec3 light_dir,
				t_color3 light_color, t_vec3 rec_normal);

// Shadow
t_bool		shadow_checker(t_object *objects, t_vec3 light_dir,
				t_hit_record rec);
t_bool		shading(t_object *objects, t_ray *ray, t_hit_record *rec);

// Plane
t_plane		*plane_init(t_point3 orig, t_vec3 normal);
t_bool		hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);

// Sphere
t_sphere	*sphere_init(t_point3 center, double diameter);
int			hit_sphere(t_sphere *sphere, t_ray *r, t_hit_record *rec);
t_bool		interfere_sphere(t_sphere *sp, t_ray *ray, double limit);

// Cylinder
t_cylinder	*cylinder_init(t_point3 orig, t_vec3 normal);

t_bool		hit_cylinder(t_cylinder *cy, t_ray *r, t_hit_record *rec);
double		hit_cylinder_surface(t_cylinder *cylinder, t_ray *r,
				t_hit_record *rec);
double		hit_cylinder_disk(t_cylinder *cy, t_ray *r, t_hit_record *rec,
				t_point3 disk_coord);
t_bool		interfere_cylinder(t_cylinder *cy, t_ray *ray, double limit);

// Square
t_square	*square_init(t_point3 center, t_vec3 normal, double side_len);
t_bool		hit_square(t_object *objects, t_ray *ray, t_hit_record *rec);

// Utils
void		nullcheck_free(void *data);
void		split_free(char **s);
void		lstclear(t_list **lst);

// Jseol .rt Parse
void		parse_file(t_scene *scene, const char *filename);
void		parse_color3(t_color3 *ret, char *color);
int			check_color3(t_color3 rgb);

void		parse_ambient(t_scene *scene, char **split);
void		parse_coords(t_vec3 *point, char *vec);
void		parse_camera(t_scene *scene, char **split);
void		parse_light(t_scene *scene, char **split);
void		parse_sphere(t_scene *scene, char **split);
void		parse_plane(t_scene *scene, char **split);
void		parse_cylinder(t_scene *scene, char **split);

double		ft_atod(char *str);
int			ft_isspace(const char c);
char		**ft_split2(char const *s, char c1, char c2);
int			split_size(char **split);
void		print_error(char *s);

int			get_next_line(int fd, char **line);
char		*ft_gnl_strjoin(char *s1, char *s2);
char		*ft_gnl_strdup(char *s);
size_t		ft_gnl_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_gnl_strlen(char *s);

#endif

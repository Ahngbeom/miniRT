/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/08 23:46:19 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*cylinder_init(t_point3 orig, t_vec3 normal)
{
	t_cylinder	*cy;

	cy = ft_calloc(sizeof(t_plane), 1);
	if (cy == NULL)
		return (NULL);
	cy->coord = orig;
	cy->dir = normal;
	cy->diameter = 14.2;
	cy->height = 21.42;
	return (cy);
}

t_bool		hit_cylinder(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3		top_center;
	t_vec3		bottom_center;
	t_vec3		hc;
	t_vec3		h;
	t_vec3		w;
	t_vec3		v;

	double		a;
	double		b;
	double		c;
	double		root;
	double		t1;
	double		t2;
	double		ttmp;
	
	top_center = vsub(cy->coord, vmul_t(cy->height, cy->dir));
	bottom_center = vsum(cy->coord, vmul_t(cy->height, cy->dir));
	hc = vsub(top_center, bottom_center);
	h = vunit(hc);
	w = vsub(r->orig, bottom_center);
	v = r->dir;
		
	a = vlength2(v) - pow(vdot(v, h), 2.0);
	b = vdot(v, w) - vdot(v, h) * vdot(w, h);
	c = vlength2(w) - pow(vdot(w, h), 2.0) - pow(cy->diameter, 2.0);

	root = pow(b, 2.0) - (4 * a * c);

	t1 = -1;
	t2 = -1;
	if (root < 0)
		return (FALSE);
	else if (root > 0)
	{
		if (b > 0)
			rec->t = -0.5 * (b + sqrt(root));
		else
			rec->t = -0.5 * (b - sqrt(root));
		t1 = rec->t / a;
		t2 = c / rec->t;
		if (t1 > t2)
		{
			ttmp = t1;
			t1 = t2;
			t2 = ttmp;
		}
	}
	else
	{
		if (fabs(vdot(v, h)) != 1)
		{
			t1 = -b / (2 * a);
			t2 = -b / (2 * a);
		}
	}

	if ((t1 < rec->tmin && t2 < rec->tmin) || (t1 > rec->tmax && t2 > rec->tmax))
		return (FALSE);
	else if (t2 < 0)
		return (FALSE);
	else if (t1 > 0)
		rec->t = t1;
	else
		rec->t = t2;

	rec->p = ray_at(r, rec->t);
	rec->normal = vunit(vsub(rec->p, cy->coord));
	rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
	rec->albedo = vmul_t(1.0 / 255.0, color);
	return (TRUE);
}

t_bool		hit_cylinder2(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3		oc;
	
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;
	
	t_vec3		h_unit;
	// double		h_len;

	h_unit = vunit(cy->dir);
	oc = vsub(r->orig, cy->coord);
	// a = vlength2(r->dir) - pow(vdot(r->dir, h_unit), 2.0);
	a = pow(vdot(r->dir, h_unit), 2.0);
	// half_b = vdot(r->dir, oc) - (vdot(r->dir, h_unit) * vdot(oc, h_unit));
	half_b = vdot(r->dir, h_unit) * vdot(oc, h_unit);
	// c = vlength2(oc) - pow(vdot(oc, h_unit), 2.0) - pow(cy->diameter / 2, 2.0);
	c = pow(vdot(oc, h_unit), 2.0) - pow(cy->diameter / 2, 2.0);
	discriminant = pow(half_b, 2.0) - a * c;
	
	if (discriminant < 0)
		return (FALSE);

	root = (-half_b - sqrt(discriminant)) / a; 
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vdiv(vsub(rec->p, vsum(cy->coord, vmul_t(cy->height, cy->dir))), cy->diameter / 2);
	set_face_normal(r, rec);
	// rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
	rec->albedo = vmul_t(1.0 / 255.0, color);
	return (TRUE);
}

t_bool		hit_cylinder_cap(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3	oc_top;
	t_vec3	oc_bot;
	double	denom;
	double	t_top;
	double	t_bot;

	cy->coord_top = vsum(cy->coord, vmul_t(cy->height / 2, cy->dir));
	cy->coord_bot = vsub(cy->coord, vmul_t(cy->height / 2, cy->dir));
	
	denom = vdot(r->dir, cy->dir);
	if (denom == 0 || denom == EPSILON)
		return (FALSE);
	
	oc_top = vsub(cy->coord_top, r->orig);
	t_top = vdot(oc_top, cy->dir) / denom;
	if (vlength(vsub(ray_at(r, t_top), cy->coord_top)) > pow(cy->diameter / 2, 2.0))
		return (FALSE);
		
	oc_bot = vsub(cy->coord_bot, r->orig);
	t_bot = vdot(oc_bot, cy->dir) / denom;
	if (vlength(vsub(ray_at(r, t_bot), cy->coord_bot)) > pow(cy->diameter / 2, 2.0))
		return (FALSE);

	if (t_top <= rec->tmin || t_top > rec->tmax)
		return (FALSE);
	if (t_bot <= rec->tmin || t_bot > rec->tmax)
		return (FALSE);
		
	if (t_top < t_bot)
		rec->t = t_top;
	else
		rec->t = t_bot;
	
	rec->albedo = vmul_t(1.0 / 255.0, color);
	return (TRUE);
}

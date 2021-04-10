/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_rev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 00:14:48 by sfalia-f          #+#    #+#             */
/*   Updated: 2021/04/10 14:44:40 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	rev_bytes_ll(long long n)
{
	return (((n & 0xff00000000000000) >> (7 * 8))
		| ((n & 0x00ff000000000000) >> (5 * 8))
		| ((n & 0x0000ff0000000000) >> (3 * 8))
		| ((n & 0x000000ff00000000) >> (1 * 8))
		| ((n & 0x00000000ff000000) << (1 * 8))
		| ((n & 0x0000000000ff0000) << (3 * 8))
		| ((n & 0x000000000000ff00) << (5 * 8))
		| ((n & 0x00000000000000ff) << (7 * 8)));
}

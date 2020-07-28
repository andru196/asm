/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_error.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 21:58:36 by andru196          #+#    #+#             */
/*   Updated: 2020/03/09 22:14:23 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ERROR_H
# define COREWAR_ERROR_H

# define MALLOC_ERROR				-1
# define SOURCE_EXTENSION_ERROR 	100
# define OPEN_FILE_ERROR			22
# define LABEL_SIZE_ERROR			-8
# define LABEL_FORBIDDEN_CHAR		-80
# define COMMAND_NOT_FOUND			-404
# define ARGS_ERROR					-101
# define PROGRAM_SIZE_LIMIT			-800
# define CONNECTION_ERROR			-777
# define NONE_QUOTE_ERROR			-409

# define MALLOC_ERROR_STR			"Memory allocation failed"
# define SOURCE_EXTENSION_ERROR_STR "Source file extension wrong"
# define OPEN_FILE_ERROR_STR		"Can't open file"
# define LABEL_SIZE_ERROR_STR		"Length of label is too big"
# define LABEL_FORBIDDEN_CHAR_STR	"Label contains forbidden character"
# define COMMAND_NOT_FOUND_STR		"Unknown command"
# define ARGS_ERROR_STR				"Error in arguments list"
# define PROGRAM_SIZE_LIMIT_STR		"Too big program"
# define CONNECTION_ERROR_STR		"Label not found"
# define NONE_QUOTE_ERROR_STR		"Argument not found"

#endif

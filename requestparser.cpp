#include "requestparser.h"
#include "request.h"

void requestparser::reset()
{
	state1=method_start;
}

bool requestparser::is_char(int c) //是否为ansi字符
{
	return c >= 0 && c <= 127;
}

bool requestparser::is_ctl(int c)
{
	return (c >= 0 && c <= 31) || (c == 127); //是否为控制字符
}

bool requestparser::is_tspecial(int c) //是不是特殊字符
{
	switch (c)
	{
		case '(': case ')': case '<': case '>': case '@':
		case ',': case ';': case ':': case '\\': case '"':
		case '/': case '[': case ']': case '?': case '=':
		case '{': case '}': case ' ': case '\t':
			return true;
		default:
			return false;
	}
}

bool requestparser::is_digit(int c) //是否为数字
{
	return c >= '0' && c <= '9';
}

requestparser::result_type requestparser::consume(request& req, char input) //分块处理请求
{
	switch (state1)
	{
		case method_start:
			if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				state1 = method;
				req.method.push_back(input);
				return uncertain; //还未完成解析
			}

		case method:
			if (input==' ') //无方法输入，默认get
			{
				state1=uri;
				return uncertain;//还未完成解析
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				req.method.push_back(input);
				return uncertain;
			}

		case uri:
			if (input == ' ') //uri分解
			{
				state1 = http_version_h;
				return uncertain;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				req.uri.push_back(input);
				return uncertain;
			}

		case http_version_h:  //跳过字符"http"
			if (input == 'H')
			{
				state1 = http_version_t_1;
				return uncertain;
			}
			else
			{
				return bad;
			}

		case http_version_t_1: //跳过字符"http"
			if (input == 'T')
			{
				state1 = http_version_t_2;
				return uncertain;
			}
			else
			{
				return bad;
			}

		case http_version_t_2: //跳过字符"http"
			if (input == 'T')
			{
				state1 = http_version_p;
				return uncertain;
			}
			else
			{
				return bad;
			}

		case http_version_p: //跳过字符"http"
			if (input == 'P')
			{
				state1 = http_version_slash;
				return uncertain;
			}
			else
			{
				return bad;
			}

		case http_version_slash: //跳过"/"
			if (input == '/')
			{
				req.http_version_major = 0;
				req.http_version_minor = 0;
				state1 = http_version_major_start;
				return uncertain;
			}
			else
			{
				return bad;
			}

		case http_version_major_start: //http大版本号
			if (is_digit(input))
			{
				req.http_version_major = req.http_version_major * 10 + input - '0';
				state1 = http_version_major;
				return uncertain;
			}
			else
			{
				return bad;
			}
		case http_version_major:
			if (input == '.')
			{
				state1 = http_version_minor_start;
				return uncertain;
			}
			else if (is_digit(input))
			{
				req.http_version_major = req.http_version_major * 10 + input - '0';
				return uncertain;
			}
			else
			{
				return bad;
			}
		case http_version_minor_start: //http小版本号
			if (is_digit(input))
			{
				req.http_version_minor = req.http_version_minor * 10 + input - '0';
				state1 = http_version_minor;
				return uncertain;
			}
			else
			{
				return bad;
			}
		case http_version_minor:
			if (input == '\r')
			{
				state1 = expecting_newline_1;
				return uncertain;
			}
			else if (is_digit(input))
			{
				req.http_version_minor = req.http_version_minor * 10 + input - '0';
				return uncertain;
			}
			else
			{
				return bad;
			}
		case expecting_newline_1:
			if (input == '\n')
			{
				state1 = header_line_start;
				return uncertain;
			}
			else
			{
				return bad;
			}
		case header_line_start:
			if (input == '\r')
			{
				state1 = expecting_newline_3;
				return uncertain;
			}
			else if (!req.headers.empty() && (input == ' ' || input == '\t'))
			{
				state1 = header_lws;
				return uncertain;
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				req.headers.push_back(header());
				req.headers.back().name.push_back(input);
				state1 = header_name;
				return uncertain;
			}
		case header_lws:
			if (input == '\r')
			{
				state1 = expecting_newline_2;
				return uncertain;
			}
			else if (input == ' ' || input == '\t')
			{
				return uncertain;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				state1 = header_value;
				req.headers.back().value.push_back(input);
				return uncertain;
			}
		case header_name:
			if (input == ':')
			{
				state1 = space_before_header_value;
				return uncertain;
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				req.headers.back().name.push_back(input);
				return uncertain;
			}
		case space_before_header_value:
			if (input == ' ')
			{
				state1 = header_value;
				return uncertain;
			}
			else
			{
				return bad;
			}
		case header_value:
			if (input == '\r')
			{
				state1 = expecting_newline_2;
				return uncertain;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				req.headers.back().value.push_back(input);
				return uncertain;
			}
			case expecting_newline_2:
				if (input == '\n')
				{
					state1 = header_line_start;
					return uncertain;
				}
				else
				{
					return bad;
				}
			case expecting_newline_3:
				return (input == '\n') ? good : bad;
			default:
				return bad;
			}
		}

		

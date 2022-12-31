#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <vector>
#include <string>

class StringUtil
{
public:
	// �ָ��ַ�����ʹ������ƥ�䣩
	static std::vector<std::string> split(const std::string& in, const std::string& delim);
	// ����������ȡ�ı�
	static std::string readText(std::istream& input);
	// �ж��Ƿ�Ϊ����
	static bool isNumber(const std::string& in);

private:

};

#endif // !STRINGUTIL_H

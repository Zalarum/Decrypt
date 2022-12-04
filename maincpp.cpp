#include <fstream>
#include <sstream>

using namespace std;

string decrypt_address(string& input, int& shift, string& alf)
{
	string ALF = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß", out = "";

	for (char i : input)
	{
		if (int(i) <= 0 && i != '¸' && i != '¹')
		{
			if (int(i) < -32) out += ALF[(alf.find(char(int(i) + 32)) + shift) % 32];
			else out += alf[(alf.find(i) + shift) % 32];
		}
		else out += i;
	}

	return out;
}

string decrypt_mail(string& input, int& shift)
{
	string alf = "abcdefghijklmnopqrstuvwxyz", out = "";

	for (char i : input)
	{
		if (int(i) >= 65)
		{
			out += alf[(alf.find(i) + shift) % 26];
		}
		else out += i;
	}

	return out;
}

int main()
{
	ofstream file_out;

	file_out.open("Decrypt.csv");

	ifstream file_in("Student_10.csv");

	string line, element, alf = "àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ";
	int shift;

	while (getline(file_in, line))
	{
		shift = alf.find('ê') - alf.find(line[line.rfind('.') - 2]);

		istringstream iss;
		iss.str(line);

		getline(iss, element, ';'); // òåëåôîíû
		file_out << " ;";

		getline(iss, element, ';'); // ìıéë
		file_out << decrypt_mail(element, shift) << ';';

		getline(iss, element, ';'); // àäğåñ
		file_out << decrypt_address(element, shift, alf) << ';' << shift << '\n';
	}

	file_in.close();

	file_out.close();

	system("Decrypt.csv");

	return 0;
}
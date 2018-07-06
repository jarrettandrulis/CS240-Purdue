#include <math.h>


int convertCharToInt(char c)
{
	if(c >= 48 && c <= 57)
		return c - '0';
	else
		return c - 'A' + 10;
}
char convertIntToChar(int i)
{
	if(i >= 0 && i <= 9)
		return i + '0';
	else
		return i + 'A' - 10;
		
}
int power(int base, int power)
{
	int total = 1;
	while(power > 0)
	{
		total *= base;
		power--;
	}
	return total;
}

void reverseString (char* str)
{
	int len = strlen(str);
	int i = 0;
	char *beg, *end;
	char hold;
	beg = str;
	end = str + len - 1;
	while( i < len/2)
	{
		hold = *beg;
		*beg = *end;
		*end = hold;
		beg++;
		end--;
		i++;
	}
}

main(int argc, char *argv[])
{
	if(argc!=4){
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
		exit(0);	
	}
	int baseFrom = atoi(argv[1]);
	int baseTo = atoi(argv[2]);
	char * number = argv[3];


	int hold = 0;
	int len = strlen(number);
	int i = 1;
	int badnum = 0;

	while( i <= len)
	{
		hold += convertCharToInt(number[len-i])*power(baseFrom,i-1);
		if(convertCharToInt(number[len-i]) > baseFrom)
		{
			badnum = 1;
		}
		i++;
	}
	char out[64];
	i = 0;
	int h = hold;
	while( hold != 0)
	{
		int holder = hold % baseTo;
		hold /= baseTo;
		out[i] = convertIntToChar(holder);
		i++;
	}
	out[i] = '\0';
	reverseString(out);
	printf("Number read in base %d: %s\n",baseFrom,number);
	if(badnum == 1)
	{
			printf("Wrong digit in number.\n");
			exit(0);	
	}
	printf("Converted to base 10: %d\n",h);
	printf("Converted to base %d: %s\n",baseTo,out);
	
}



// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	int arr1[32];
	int arr2[32];
	int i = 31;
	int j;
	while(i >= 0)
	{
		arr1[i] = bitmap % 2;
		bitmap /= 2;
		i--;
	}
	i = 31;
	while(i >= 0)
	{
		while( j <= 9 && i >=0)
		{
			arr2[i] = j;
			j++;
			i--;
		}
		j = 0;
	}
	i = 0;
	while(i<32)
	{
		printf("%d",arr1[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while(i<32)
	{
		printf("%d",arr2[i]);
		i++;
	}
	printf("\n"); 

}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	*bitmap &= ~(1 << i);
	*bitmap |= bitValue << i;
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	return 1 & (bitmap >> i);
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	int counter = 0;
	int i = 0;
	while( i < 32)
	{
		if(getBitAt(bitmap, i) == bitValue)
			counter++;
		i++;
	}
	return counter;

}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	int counter = 0;
	int max = 0;
	int maxStart;
	int i = 0;
	while( i < 32)
	{
		if(getBitAt(bitmap, i))
		{
			if(counter == 0)
				maxStart = i;
			counter++;
			if(counter > max)
			{
				*position = maxStart;
				max = counter;
			}
		}
		else
		{
			counter = 0;
		}
			
		i++;
	}
	return max;

}



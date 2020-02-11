extern int total;
extern int count;

double average()
{
	double avg = 0;

	avg = total / (double)count;

	return avg;
}
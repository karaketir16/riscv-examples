

void my_f (void) __attribute__ ((interrupt ("machine")));
void my_f (void)
{
    int x = 0;
    int y = 1;
    int z = x + y;
}

void my_f2 (void)
{
    int x = 0;
    int y = 1;
    int z = x + y;
}
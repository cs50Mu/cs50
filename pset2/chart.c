/*
 * stupid chart bar
 */

 #include <cs50.h>
 #include <stdio.h>

void GenBar(int n);

int main(void)
 {
    printf("M spotting F: ");
    int mf = GetInt();
    printf("F spotting M: ");
    int fm = GetInt();
    printf("F spotting F: ");
    int ff = GetInt();
    printf("M spotting M: ");
    int mm = GetInt();
    printf("\n\nWho is Spotting Whom\n\n");
    float sum = mf + fm + ff + mm;
    printf("M spotting F\n");
    GenBar((int) (80 * ( mf / sum)));
    printf("F spotting M\n");
    GenBar((int) (80 * ( fm / sum)));
    printf("F spotting F\n");
    GenBar((int) (80 * ( ff / sum)));
    printf("M spotting M\n");
    GenBar((int) (80 * ( mm / sum)));
 }

void GenBar(int n)
{
    for(int i=0;i<n;i++)
    {
        printf("#");
    }
    printf("\n");
}

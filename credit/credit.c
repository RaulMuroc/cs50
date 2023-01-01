#include <cs50.h>
#include <stdio.h>

int main(void)
{
  long numberCard;
  do
  {
    numberCard = get_long("card no:");
  } while (numberCard < 0);

  int card1, card2, card3, card4, card5, card6, card7, card8;
  card1 = (( numberCard % 100 ) / 10 ) * 2;
  card2 = (( numberCard % 10000 ) / 1000 ) * 2;
  card3 = (( numberCard % 1000000 ) / 100000 ) * 2;
  card4 = (( numberCard % 100000000 ) / 10000000 ) * 2;
  card5 = (( numberCard % 10000000000 ) / 1000000000 ) * 2;
  card6 = (( numberCard % 1000000000000 ) / 100000000000 ) * 2;
  card7 = (( numberCard % 100000000000000 ) / 10000000000000 ) * 2;
  card8 = (( numberCard % 10000000000000000 ) / 1000000000000000 ) * 2;

  card1 = ( card1 % 100 / 10) + ( card1 % 10);
  card2 = ( card2 % 100 / 10) + ( card2 % 10);
  card3 = ( card3 % 100 / 10) + ( card3 % 10);
  card4 = ( card4 % 100 / 10) + ( card4 % 10);
  card5 = ( card5 % 100 / 10) + ( card5 % 10);
  card6 = ( card6 % 100 / 10) + ( card6 % 10);
  card7 = ( card7 % 100 / 10) + ( card7 % 10);
  card8 = ( card8 % 100 / 10) + ( card8 % 10);

  int sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;


  int card9, card10, card11, card12, card13, card14, card15, card16;
  card9 = (( numberCard % 10 ));
  card10 = (( numberCard % 1000 ) / 100 );
  card11 = (( numberCard % 100000 ) / 10000 );
  card12 = (( numberCard % 10000000 ) / 1000000 );
  card13 = (( numberCard % 1000000000 ) / 100000000 );
  card14 = (( numberCard % 100000000000 ) / 10000000000 );
  card15 = (( numberCard % 10000000000000 ) / 1000000000000 );
  card16 = (( numberCard % 1000000000000000 ) / 100000000000000 );

  int sum2 = card9 + card10 + card11 + card12 + card13 + card14 + card15 + card16;
  int sum3 = sum1 + sum2;

  int length = 0;
  long visa = numberCard;
  long amex = numberCard;
  long master = numberCard;

  if (( sum3 % 10 ) != 0)
  {
     printf("%s\n", "INVALID");
     return 0;
  }

  while (numberCard > 0)
  {
    numberCard = numberCard / 10;
    length++;
  }

  while (visa >= 10)
  {
    visa /= 10;
  }
  if ( visa == 4 && (length == 13 || length == 16))
  {
    printf("%s\n", "VISA");
    return 0;
  }

  while (amex >= 10000000000000)
  {
    amex /= 10000000000000;
  }
  if ( length == 15 && ( amex == 34 ||amex == 37))
  {
    printf("%s\n", "AMEX");
    return 0;
  }

  while (master >= 100000000000000)
  {
    master /= 100000000000000;
  }
  if ( length == 16 && ( master == 51 ||amex == 52||amex == 53||amex == 54||amex == 55))
  {
    printf("%s\n", "MASTERCARD");
    return 0;
  }
  else
  {
    printf("%s\n", "INVALID");
    return 0;
  }

}
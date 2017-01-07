/* Hamming Encoding and Decoding functions
  For ELEC 405 Class at UVic

  Developed by: Marc Laventure

 */

#include <stdlib.h>
#include <stdio.h>

#define ORIGINAL_MESSAGE_SIZE 4
#define ENCODED_MESSAGE_SIZE 7
#define DECODED_MESSAGE_SIZE 7

int *Hamming74_encode(int pMessage[])
{
  int *ret = malloc(sizeof(int *) * ENCODED_MESSAGE_SIZE);
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    ret[i] = pMessage[i];
  }
  ret[4] = (pMessage[1] + pMessage[2] + pMessage[3]) % 2;
  ret[5] = (pMessage[0] + pMessage[1] + pMessage[3]) % 2;
  ret[6] = (pMessage[0] + pMessage[2] + pMessage[3]) % 2;
  return ret;
}

void outputMessages(int pOriginal[], int pEncoded[])
{
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    printf("%d ", pOriginal[i]);
  }
  printf("\n");
  for (int i = 0; i < ENCODED_MESSAGE_SIZE; i++)
  {
    printf("%d ", pEncoded[i]);
  }
  printf("\ndone\n");
}

int main(void)
{
  // This is for testing purposes at the moment.
  int message[] = {0, 0, 1, 0};
  int *sentMessage;
  sentMessage = Hamming74_encode(message);
  outputMessages(message, sentMessage);

  free(sentMessage);
  return 0;
}
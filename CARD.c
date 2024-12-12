#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
typedef enum esuit {
  SPADES = 50,
  HEARTS = 40,
  CLUBS = 30,
  DIAMONDS = 20,
} Suit;

typedef enum eface {
  ACE = 14,
  DEUCE = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9,
  TEN = 10,
  JACK = 11,
  QUEEN = 12,
  KING = 13,
} Face;

typedef struct Card {
  Suit suit;
  Face face;
} Card;

typedef Card Hand[5];
bool InputHand(Hand hand);
bool BiggerThan(Card card1, Card card2);
Card FindLargest(Hand hand);
bool IsFlush(Hand hand);
bool IsStraight(Hand hand);
bool IsStraightFlush(Hand hand);
bool IsFourOfAKind(Hand hand);
bool HasThreeOfAKind(Hand hand);
bool HasOnePair(Hand hand);
bool IsTwoPairs(Hand hand);
bool IsFullHouse(Hand hand);
void BubbleSwap(Hand hand) { // 由小到大
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4-i; j++) {
      if (BiggerThan(hand[j], hand[j+1])) {
        Card temp = hand[j+1];
        hand[j+1] = hand[j];
        hand[j] = temp;
      }
    }
  }
}
Card FourLargest(Hand hand) {
  Card fourofakind[5] = {0};
  int face = 0;
  for (int i = 0; i <= 1; i++) {
    if (hand[i].face == hand[i + 1].face &&
        hand[i].face == hand[i + 2].face &&
        hand[i].face == hand[i + 3].face) face = hand[i].face;
  }
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == face) {
      fourofakind[i] = hand[i];
    }
  }
  Card biggest = FindLargest(fourofakind);
  return biggest;
}
Card ThreeLargest(Hand hand) {
  Card threeofakind[5] = {0};
  int same_face = 0;
  for (int i = 0; i < 3; i++) {
    if (hand[i+1].face  == hand[i].face &&
        hand[i+1].face  == hand[i+2].face) same_face = hand[i].face;
  }
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == same_face) {
      threeofakind[i] = hand[i];
    }
  }
  Card biggest = FindLargest(threeofakind);
  return biggest;
}
Card FullLargest(Hand hand) {
  Card fullhou[5] = {0};
  int three_same = 0;
  for (int i = 0; i < 3; i++) {
    if (hand[i].face == hand[i+1].face && hand[i].face == hand[i+2].face) {
      three_same = hand[i].face;
      break;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == three_same) fullhou[i] = hand[i];
  }
  Card biggest = FindLargest(fullhou);
  return biggest;
}
int TwoPairFace1(Hand hand) { // 找最大對的面值
  Card twopair[5] = {0};
  BubbleSwap(hand);
  int four_space = 0;
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) {
      twopair[four_space] = hand[i];
      four_space++;
      twopair[four_space] = hand[i+1];
      four_space++;
    }
  }
  int face1 = twopair[3].face;
  return face1;
}
int TwoPairFace2(Hand hand) { // 找第二大對的面值
  Card twopair[5] = {0};
  BubbleSwap(hand);
  int four_space = 0;
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) {
      twopair[four_space] = hand[i];
      four_space++;
      twopair[four_space] = hand[i+1];
      four_space++;
    }
  }
  int face2 = twopair[1].face;
  return face2;
}
Card TwoPairLargest1(Hand hand) {
  Card twopair[5] = {0};
  BubbleSwap(hand);
  int four_space = 0;
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) {
      twopair[four_space] = hand[i];
      four_space++;
      twopair[four_space] = hand[i+1];
      four_space++;
    }
  }
  Card biggest = twopair[1];
  return biggest;
}
Card TwoPairLargest2(Hand hand) {
  Card twopair[5] = {0};
  BubbleSwap(hand);
  int four_space = 0;
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) {
      twopair[four_space] = hand[i];
      four_space++;
      twopair[four_space] = hand[i+1];
      four_space++;
    }
  }
  Card biggest = twopair[3];
  return biggest;
}

Card OnePairLargest(Hand hand) {
  Card onepair[5] = {0};
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) {
      onepair[2] = hand[i];
      onepair[4] = hand[i+1];
      break;
    }
  }
  Card largest = FindLargest(onepair);
  return largest;
}

void SwitchFace(int face_num, char face[10]) {
  if (face_num == ACE) strcpy(face, "Ace");
  else if (face_num == DEUCE) strcpy(face, "Deuce");
  else if (face_num == THREE) strcpy(face, "Three");
  else if (face_num == FOUR) strcpy(face, "Four");
  else if (face_num == FIVE) strcpy(face, "Five");
  else if (face_num == SIX) strcpy(face, "Six");
  else if (face_num == SEVEN) strcpy(face, "Seven");
  else if (face_num == EIGHT) strcpy(face, "Eight");
  else if (face_num == NINE) strcpy(face, "Nine");
  else if (face_num == TEN) strcpy(face, "Ten");
  else if (face_num == JACK) strcpy(face, "Jack");
  else if (face_num == QUEEN) strcpy(face, "Queen");
  else strcpy(face, "King");
}
void HandType(int score, char handType[20]) {
  if (score == 9) strcpy(handType, "Straight flush");
  else if (score == 8) strcpy(handType, "Four of a kind");
  else if (score == 7) strcpy(handType, "Full house");
  else if (score == 6) strcpy(handType, "Flush");
  else if (score == 5) strcpy(handType, "Straight");
  else if (score == 4) strcpy(handType, "Three of a kind");
  else if (score == 3) strcpy(handType, "Two pairs");
  else if (score == 2) strcpy(handType, "One pair");
  else if (score == 1)strcpy(handType, "Zilch");
}

void SwitchSuit(int suit_num, char suit[10]) {
  if (suit_num == SPADES) strcpy(suit, "Spades");
  else if (suit_num == HEARTS) strcpy(suit, "Hearts");
  else if (suit_num == CLUBS) strcpy(suit, "Clubs");
  else strcpy(suit, "Diamonds");
}
int EvaluateHand(Hand hand) {
  int score = 0;
  if (IsStraightFlush(hand)) score = 9;
  else if (IsFourOfAKind(hand)) score = 8;
  else if (IsFullHouse(hand)) score = 7;
  else if (IsFlush(hand)) score = 6;
  else if (IsStraight(hand))  score = 5;
  else if (HasThreeOfAKind(hand)) score = 4;
  else if (IsTwoPairs(hand)) score = 3;
  else if (HasOnePair(hand)) score = 2;
  else score = 1;
  return score;
}
Card EvaluateLargest(Hand hand, int score) {
  Card largest;
  if (score == 9) largest = FindLargest(hand); // 桐花順
  else if (score == 8) largest = FourLargest(hand); // 鐵支
  else if (score == 7) largest =  FullLargest(hand); // 葫蘆
  else if (score == 6) largest =  FindLargest(hand); // 桐花
  else if (score == 5) largest  =  FindLargest(hand); // 順子
  else if (score == 4) largest = ThreeLargest(hand);
  else if (score == 3) largest = TwoPairLargest2(hand); // 較大對子的較大牌
  else if (score == 2) largest = OnePairLargest(hand);
  else if (score == 1)largest = FindLargest(hand);
  return largest;
}
void Play(Hand hand1, Hand hand2) {
  int score1 = EvaluateHand(hand1);
  int score2 = EvaluateHand(hand2);
  Card maxcard1 =  EvaluateLargest(hand1, score1);
  Card maxcard2 = EvaluateLargest(hand2, score2);
  // 牌型名稱轉換
  char handType1[20], handType2[20];
  HandType(score1, handType1);
  HandType(score2, handType2);
  handType2[0] += ('a' - 'A');

  // 花色名稱轉換
  char suit1[10], suit2[10];
  SwitchSuit(maxcard1.suit, suit1);
  SwitchSuit(maxcard2.suit, suit2);
  // 點數名稱轉換
  char face1[10], face2[10];
  SwitchFace(maxcard1.face, face1);
  SwitchFace(maxcard2.face, face2);

  char final1[100];
  sprintf(final1, "%s of %s", face1, suit1);  // final == face of suit
  char final2[100];
  sprintf(final2, "%s of %s", face2, suit2);

  // 找較小對子的較大牌
  if (score1 == 3) {
    Card sec_lar1 = TwoPairLargest1(hand1);
    char pair_face1[20];
    char pair_suit1[20];
    SwitchFace(sec_lar1.face, pair_face1);
    SwitchSuit(sec_lar1.suit, pair_suit1);
    strcat(final1, " and ");
    strcat(final1,  pair_face1);
    strcat(final1, " of ");
    strcat(final1, pair_suit1);
  }
  if (score2 == 3) {
    Card sec_lar2 = TwoPairLargest1(hand2);
    char pair_face2[20];
    char pair_suit2[20];
    SwitchFace(sec_lar2.face, pair_face2);
    SwitchSuit(sec_lar2.suit, pair_suit2);
    strcat(final2, " and ");
    strcat(final2,  pair_face2);
    strcat(final2, " of ");
    strcat(final2, pair_suit2);
  }
  // 如果都是two pairs
  if (score1 == 3 && score2 == 3) {
    int face1_1, face1_2, face2_1, face2_2;
    face1_1 = TwoPairFace1(hand1); // 玩家一 第一對
    face1_2 = TwoPairFace2(hand1); // 玩家一 第二對
    face2_1 = TwoPairFace1(hand2); // 玩家二 第一對
    face2_2 = TwoPairFace2(hand2); // 玩家一 第一對
    if (face1_1 > face2_1) {
      printf("%s (%s) wins over %s (%s).",
          handType1, final1, handType2, final2);
    }

    else if (face1_1 < face2_1) {
      printf("%s (%s) loses to %s (%s).",
          handType1, final1, handType2, final2);
    }

    else if (face1_1 == face2_1) {
      if (face1_2 > face2_2) {
        printf("%s (%s) wins over %s (%s).",
            handType1, final1, handType2, final2);
      }

      else if (face1_2 < face2_2) {
        printf("%s (%s) loses to %s (%s).",
            handType1, final1, handType2, final2);
      }

      else if (face1_2 == face2_2) {
        if (BiggerThan(maxcard1, maxcard2)) {
          printf("%s (%s) wins over %s (%s).",
              handType1, final1, handType2, final2);
        }

        else if (BiggerThan(maxcard2, maxcard1)) {
          printf("%s (%s) loses to %s (%s).",
              handType1, final1, handType2, final2);
        }
      }

    }
  }
  // 比較兩手牌
  else if (score1 > score2) {
    printf("%s (%s) wins over %s (%s).",
        handType1, final1, handType2, final2);
  }

  else if (score1 < score2) {
    printf("%s (%s) loses to %s (%s).",
        handType1, final1, handType2, final2);
  }

  else if (score1 == score2) {
    // 如果牌型相同，則進一步比較最大牌
    if (BiggerThan(maxcard1, maxcard2)) {
      printf("%s (%s) wins over %s (%s).",
          handType1, final1, handType2, final2);
    }

    else if (BiggerThan(maxcard2, maxcard1)) {
      printf("%s (%s) loses to %s (%s).",
          handType1, final1, handType2, final2);
    }
  }
}
int main() {
  Hand firsthand, secondhand;

  if (InputHand(firsthand)) {
    BubbleSwap(firsthand);
    if (InputHand(secondhand)) {
      BubbleSwap(secondhand);
      Play(firsthand, secondhand);
    } else   // second input set not okay
      printf("Input Error in second hand of cards!\n");
  } else {  // first input set not okay
    printf("Input Error in first hand of cards!\n");
  }
  return 0;
}

bool InputHand(Hand hand) {
  char suit_char;
  char face_str[10];
  int card_count = 0;

  while (1) {
    scanf(" %c", &suit_char);
    if (suit_char == '-') {
      int n;
      scanf("%d", &n);
      break;
    }
    scanf(" %s", face_str);
    int suit;
    if (suit_char == 'S') {
      suit = SPADES;
    }

    else if (suit_char == 'H') {
      suit = HEARTS;
    }

    else if (suit_char == 'D') {
      suit = DIAMONDS;
    }

    else if (suit_char == 'C') {
      suit = CLUBS;
    }

    else return false;

    int face = -1;
    if (strcmp(face_str, "A") == 0) face = ACE;
    else if (strcmp(face_str, "2") == 0) face = DEUCE;
    else if (strcmp(face_str, "3") == 0) face = THREE;
    else if (strcmp(face_str, "4") == 0) face = FOUR;
    else if (strcmp(face_str, "5") == 0) face = FIVE;
    else if (strcmp(face_str, "6") == 0) face = SIX;
    else if (strcmp(face_str, "7") == 0) face = SEVEN;
    else if (strcmp(face_str, "8") == 0) face = EIGHT;
    else if (strcmp(face_str, "9") == 0) face = NINE;
    else if (strcmp(face_str, "10") == 0) face = TEN;
    else if (strcmp(face_str, "J") == 0) face = JACK;
    else if (strcmp(face_str, "Q") == 0) face = QUEEN;
    else if (strcmp(face_str, "K") == 0) face = KING;
    else return false;

    hand[card_count].suit = suit;
    hand[card_count].face = face;
    card_count++;
  }

  if (card_count != 5) return false;
  return true;
}
int Order1(Face face) {
  if (face == ACE)  return 14;
  else if (face == DEUCE) return 2;
  else if (face == THREE) return 3;
  else if (face == FOUR) return 4;
  else if (face == FIVE) return 5;
  else if (face == SIX) return 6;
  else if (face == SEVEN) return 7;
  else if (face == EIGHT) return 8;
  else if (face == NINE) return 9;
  else if (face == TEN) return 10;
  else if (face == JACK) return 11;
  else if (face == QUEEN) return 12;
  else if (face == KING) return 13;

  else return 0;

}

int Order2(Suit suit) {
  if (suit == SPADES) return 4;
  if (suit == HEARTS) return 3;
  if (suit == CLUBS) return 2;
  if (suit == DIAMONDS) return 1;
}


bool BiggerThan(Card card1, Card card2) {
  int face1 = Order1(card1.face); // bus
  int face2 = Order1(card2.face);
  int suit1 = Order2(card1.suit);
  int suit2 = Order2(card2.suit);

  if (face1 > face2) return true;
  else if (face2 > face1) return false;
  else {
    if (suit1 > suit2) return true;
    else if (suit2 > suit1) return false;
    else return false;
  }
}
Card FindLargest(Hand hand) {
  int special_stra[5] = {0};
  int is_special = true;
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == ACE) special_stra[0] = 1;
    if (hand[i].face == DEUCE) special_stra[1] = 1;
    if (hand[i].face == THREE) special_stra[2] = 1;
    if (hand[i].face == FOUR) special_stra[3] = 1;
    if (hand[i].face == FIVE) special_stra[4] = 1;
  }
  for (int i = 0; i < 5; i++) {
    if (!special_stra[i]) is_special = false;
  }

  if (is_special) {
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == FIVE) return hand[i];
    }
  }

  else {
    Card largest = hand[0];
    for (int i = 1; i < 5; i++) {
      if (BiggerThan(hand[i], largest)) largest = hand[i];
    }
    return largest;
  }
}
bool IsFlush(Hand hand) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (hand[i].suit != hand[j].suit) return false;
    }
  }
  return true;
}
int OrderSpecial(Face face) { // A最小
  if (face == ACE)  return 1;
  else if (face == DEUCE) return 2;
  else if (face == THREE) return 3;
  else if (face == FOUR) return 4;
  else if (face == FIVE) return 5;
  else if (face == SIX) return 6;
  else if (face == SEVEN) return 7;
  else if (face == EIGHT) return 8;
  else if (face == NINE) return 9;
  else if (face == TEN) return 10;
  else if (face == JACK) return 11;
  else if (face == QUEEN) return 12;
  else if (face == KING) return 13;

  else return 0;
}
bool IsStraight(Hand hand) {
  bool is_special = false;
  int face_array[5] = {0};
  for (int i = 0; i < 5; i++) {
    if (Order1(hand[i].face) == 2) is_special = true;
  }

  if (is_special) {
    for (int i = 0; i < 5; i++) {
      face_array[i] = OrderSpecial(hand[i].face);
    }
  }

  else {
    for (int i = 0; i < 5; i++) {
      face_array[i] = Order1(hand[i].face);
    }
  }

  for (int i = 0; i < 4; i++) { // sort
    for (int j = 0; j < 5-1-i; j++)
      if (face_array[j] < face_array[j+1]) {
        int temp = face_array[j];
        face_array[j] = face_array[j+1];
        face_array[j+1] = temp;
      }
  }

  bool is_straight = true;
  for (int i = 0; i < 4; i++) {
    if (face_array[i] - face_array[i+1] != 1) {
      is_straight = false;
      return false;
    }
  }
  return true;
}
bool IsStraightFlush(Hand hand) {
  if (IsStraight(hand) && IsFlush(hand)) {
    return true;
  }
  return false;  // just to tell you that you should return a boolean value
}
bool IsFourOfAKind(Hand hand) {
  BubbleSwap(hand);
  for (int i = 0; i < 2; i++) {
    if (hand[i].face == hand[i + 1].face &&
        hand[i].face == hand[i + 2].face &&
        hand[i].face == hand[i + 3].face) return true;
  }

  return false;
}
bool HasThreeOfAKind(Hand hand) {
  BubbleSwap(hand);
  for (int i = 0; i < 3; i++) {
    if (hand[i].face == hand[i+1].face && hand[i].face == hand[i+2].face) {
      return true;
    }
  }
  return false;
}
bool HasOnePair(Hand hand) {
  BubbleSwap(hand);
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) return true;
  }
  return false;
}
bool IsTwoPairs(Hand hand) {
  BubbleSwap(hand);
  int count = 0;
  for (int i = 0; i < 4; i++) {
    if (hand[i].face == hand[i+1].face) count++;
  }

  if (count == 2) return true;
  return false;
}
bool IsFullHouse(Hand hand) {
  BubbleSwap(hand);
  if ((hand[0].face == hand[1].face && hand[1].face == hand[2].face &&
          hand[3].face == hand[4].face && hand[2].face != hand[3].face) ||
      (hand[0].face == hand[1].face && hand[2].face == hand[3].face &&
          hand[3].face == hand[4].face && hand[1].face != hand[2].face)) {
    return true;
  }
  return false;

}


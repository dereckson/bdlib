/* StringTest.c
 *
 * $Id$
 */
#include <ctype.h>
#include "StringTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (StringTest);

void StringTest :: setUp (void)
{
    strcpy(cstring, "Some static cstring to play with");
    // set up test environment (initializing objects)
    a = new String();
    b = new String("blah");
    c = new String(*b);
    d = new String(cstring);
    e = new String(*d);
    f = new String(cstring, 11);
    g = new String('x');
    h = new String(35);
}

void StringTest :: tearDown (void)
{
    // finally delete objects
    delete a; delete b; delete c; delete d;
    delete e; delete f; delete g; delete h;
}

void StringTest :: lengthTest (void)
{
  CPPUNIT_ASSERT_EQUAL((size_t) 0, a->length());
  CPPUNIT_ASSERT_EQUAL((size_t) 4, b->length());
  CPPUNIT_ASSERT_EQUAL(b->length(), c->length());
  CPPUNIT_ASSERT_EQUAL(strlen(cstring), d->length());
  CPPUNIT_ASSERT_EQUAL(d->length(), e->length());
  CPPUNIT_ASSERT_EQUAL((size_t) 11, f->length());
  CPPUNIT_ASSERT_EQUAL((size_t) 1, g->length());
  CPPUNIT_ASSERT_EQUAL((size_t) 0, h->length());
}

void StringTest :: capacityTest (void)
{
  CPPUNIT_ASSERT(b->capacity() >= 4);
  CPPUNIT_ASSERT_EQUAL(b->capacity(), c->capacity());
  CPPUNIT_ASSERT(d->capacity() >= strlen(cstring));
  CPPUNIT_ASSERT_EQUAL(d->capacity(), e->capacity());
  CPPUNIT_ASSERT(f->capacity() >= 11);
  CPPUNIT_ASSERT(g->capacity() >= 1);
  CPPUNIT_ASSERT(h->capacity() >= 35);
}

void StringTest :: compareTest (void)
{
  CPPUNIT_ASSERT_EQUAL(0, (*b).compare("blah"));
  CPPUNIT_ASSERT_EQUAL(0, (*d).compare(cstring));
  CPPUNIT_ASSERT_EQUAL(0, (*f).compare(cstring, 11));
  CPPUNIT_ASSERT((*f).compare(cstring) < 0);
  CPPUNIT_ASSERT((*d).compare(*f) > 0);
  CPPUNIT_ASSERT_EQUAL(0, (*b).compare(*c));
}

void StringTest :: equalTest (void)
{
  CPPUNIT_ASSERT_EQUAL (*b, *c);
  CPPUNIT_ASSERT_EQUAL (*b, String("blah"));
  CPPUNIT_ASSERT_STRING_EQUAL ("blah", *b);
  CPPUNIT_ASSERT_EQUAL (*d, String(cstring));
  CPPUNIT_ASSERT_STRING_EQUAL (cstring, *d);
  CPPUNIT_ASSERT_EQUAL (*e, String(cstring));
  CPPUNIT_ASSERT_STRING_EQUAL (cstring, *e);
  CPPUNIT_ASSERT_EQUAL (*g, String('x'));
  CPPUNIT_ASSERT_STRING_EQUAL ('x', *g);
  CPPUNIT_ASSERT_EQUAL (*g, String("x"));
  CPPUNIT_ASSERT_STRING_EQUAL ("x", *g);
  CPPUNIT_ASSERT(!(*b != *c));
  CPPUNIT_ASSERT_EQUAL(true, !(*a));
  CPPUNIT_ASSERT_EQUAL(false, !(*b));
}

void StringTest :: setTest (void)
{
  *a = "blah";
  CPPUNIT_ASSERT_STRING_EQUAL ("blah", *a);
  CPPUNIT_ASSERT_EQUAL(*a, *b);
  *h = cstring;
  CPPUNIT_ASSERT_EQUAL(*d, *h);
  *a = "  ";
  CPPUNIT_ASSERT_STRING_EQUAL("  ", *a);
  *b = ' ';
  CPPUNIT_ASSERT_STRING_EQUAL(" ", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *c);
  *b = *c;
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *b);
  *b = *b;
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *b);
}

void StringTest :: c_strTest(void)
{
  const char *b_test = b->c_str();
  const char *c_test = c->c_str();
  const char *d_test = d->c_str();
  const char *e_test = e->c_str();
  const char *f_test = f->c_str();

  CPPUNIT_ASSERT_EQUAL(0, strcmp(b_test, "blah"));
  CPPUNIT_ASSERT_EQUAL(0, strcmp(b_test, c_test));
  CPPUNIT_ASSERT_EQUAL(0, strcmp(d_test, cstring));
  CPPUNIT_ASSERT_EQUAL(0, strcmp(d_test, e_test));
  CPPUNIT_ASSERT(strcmp(f_test, d_test) < 0);
}

void StringTest :: hasIndexTest(void)
{
  CPPUNIT_ASSERT_EQUAL(false, a->hasIndex(0));
  CPPUNIT_ASSERT_EQUAL(true, b->hasIndex(3));
  CPPUNIT_ASSERT_EQUAL(false, b->hasIndex(4));
  CPPUNIT_ASSERT_EQUAL(true, f->hasIndex(10));
  CPPUNIT_ASSERT_EQUAL(false, f->hasIndex(11));
}

void StringTest :: charAtTest(void)
{
  CPPUNIT_ASSERT_EQUAL('b', b->charAt(0));
  CPPUNIT_ASSERT_EQUAL('h', b->charAt(3));
  CPPUNIT_ASSERT_EQUAL((char) 0, b->charAt(4));
  CPPUNIT_ASSERT_EQUAL(cstring[5], d->charAt(5));
  CPPUNIT_ASSERT_EQUAL('x', g->charAt(0));
}

void StringTest :: indexTest(void)
{
  CPPUNIT_ASSERT_EQUAL('b', (char) (*b)[0]);
  CPPUNIT_ASSERT_EQUAL('h', (char) (*b)[3]);
  CPPUNIT_ASSERT_EQUAL(cstring[5], (char) (*d)[5]);
  CPPUNIT_ASSERT_EQUAL('x', (char) (*g)[0]);

  (*a) = "This is a test";
  (*b) = (*a);
  (*b)[0] = 't';
  (*b)[1] = 'H';
  (*b)[2] = (char) (*b)[1];
  (*b)[3] = ((const String) *a)[0];
  (*b)[5] = (*a)[6];
  char chr = (*a)[6];

  (*b)[6] = (*b)[7] = 'a';
  CPPUNIT_ASSERT_EQUAL('a', (char) (*b)[6]);
  CPPUNIT_ASSERT_EQUAL('a', (char) (*b)[7]);

  (*b)[6] = (*b)[7] = (*a)[0];

  (*b)[6] = (*b)[6] = (*b)[6];
 
  CPPUNIT_ASSERT_EQUAL('s', chr);

  CPPUNIT_ASSERT_STRING_EQUAL("This is a test", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("tHHT sTTa test", *b);
}

void StringTest :: iteratorTest(void)
{
  (*a) = (*b) = "this is just a TEST";

  for (size_t i = 0; i < (*a).length(); ++i)
    (*a)[i] = toupper((*a)[i]);

  CPPUNIT_ASSERT_STRING_EQUAL("THIS IS JUST A TEST", (*a));  
  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", (*b));

  for (size_t i = 0; i < (*a).length() - 1; ++i)
    (*a)[i] = (*b)[i+1] = tolower((*a)[i]);

  CPPUNIT_ASSERT_STRING_EQUAL("this is just a tesT", (*a));  
  CPPUNIT_ASSERT_STRING_EQUAL("tthis is just a tes", (*b));
}

void StringTest :: appendTest(void)
{
  a->append('a');
  CPPUNIT_ASSERT_EQUAL(0, strcmp(a->c_str(), "a"));
  a->append("bcd");
  CPPUNIT_ASSERT_STRING_EQUAL("abcd", *a);
  a->append("test", 0);
  CPPUNIT_ASSERT_STRING_EQUAL("abcd", *a);
  f->append(&cstring[11], strlen(cstring) - 11);
  CPPUNIT_ASSERT_STRING_EQUAL(*d, *f);
  c->append(*b);
  CPPUNIT_ASSERT_STRING_EQUAL("blahblah", *c);
  c->append(' ');
  c->append(*c);
  CPPUNIT_ASSERT_STRING_EQUAL("blahblah blahblah ", *c);
  c->append("  ");
  c->append(*b);
  CPPUNIT_ASSERT_STRING_EQUAL("blahblah blahblah   blah", *c);

  /* Test binary data! */
  String tmp(255);
  for (unsigned char c = 0; c < 255; c++)
    tmp.append(c);
  CPPUNIT_ASSERT_EQUAL((size_t)255, tmp.length());

  char *s = (char*) malloc(255);
  for (unsigned char c = 0; c < 255; c++)
    s[(unsigned int) c] = c;
  String tmp2 = String(s, 255);

  CPPUNIT_ASSERT_STRING_EQUAL(tmp2, tmp);
  CPPUNIT_ASSERT_EQUAL(tmp.length(), tmp2.length());
  free(s);

}

void StringTest :: insertTest(void)
{
  a->insert(1, 'a');
  CPPUNIT_ASSERT_EQUAL(false, a->hasIndex(0));
  a->insert(0, 'b');
  CPPUNIT_ASSERT_STRING_EQUAL("b", *a);
  CPPUNIT_ASSERT_EQUAL(false, a->hasIndex(1));
  b->insert(2, "BLAH");
  CPPUNIT_ASSERT_STRING_EQUAL("blBLAHah", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *c);
  b->insert(3, "TEST", 0);
  CPPUNIT_ASSERT_STRING_EQUAL("blBLAHah", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *c);
  b->insert(3, "TEST", 1);
  CPPUNIT_ASSERT_STRING_EQUAL("blBTLAHah", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *c);
}

void StringTest :: replaceTest(void)
{
  a->replace(1, "wtf");
  CPPUNIT_ASSERT_EQUAL(false, a->hasIndex(0));
  b->replace(1, 'x');
  CPPUNIT_ASSERT_STRING_EQUAL("bxah", *b);
  b->replace(0, "haha");
  CPPUNIT_ASSERT_STRING_EQUAL("haha", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *c);
  g->replace(1, "ml");
  CPPUNIT_ASSERT_STRING_EQUAL("xml", *g);
}

void StringTest :: concatTest(void)
{
 *a = *b + " " + *b;
 CPPUNIT_ASSERT_STRING_EQUAL("blah blah", *a);
 *a = *b + *a;
 CPPUNIT_ASSERT_STRING_EQUAL("blahblah blah", *a);
 delete a;
 a = new String();
 *a = *b + *a;
 CPPUNIT_ASSERT_STRING_EQUAL("blah", *a);
}

void StringTest :: incDecTest(void)
{
  *a = "test";
  CPPUNIT_ASSERT_STRING_EQUAL("test", *a);
  String old = (*a)++;
  CPPUNIT_ASSERT_STRING_EQUAL("test", old);
  CPPUNIT_ASSERT_STRING_EQUAL("est", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 3, a->length());
  ++(*a);
  CPPUNIT_ASSERT_STRING_EQUAL("st", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 2, a->length());
  old = (*a)--;
  CPPUNIT_ASSERT_STRING_EQUAL("st", old);
  CPPUNIT_ASSERT_STRING_EQUAL("s", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 1, a->length());
  --(*a);
  CPPUNIT_ASSERT_STRING_EQUAL("", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 0, a->length());
}

void StringTest :: incDecEqualTest(void)
{
  *a += "longtest";
  CPPUNIT_ASSERT_STRING_EQUAL("longtest", *a);
  *a -= 3;
  CPPUNIT_ASSERT_STRING_EQUAL("longt", *a);
  *a += 4;
  CPPUNIT_ASSERT_STRING_EQUAL("t", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 1, a->length());
  *a += *b;
  CPPUNIT_ASSERT_STRING_EQUAL("tblah", *a);
  CPPUNIT_ASSERT_EQUAL((size_t) 5, a->length());

  *d += *d + *d;
  char check[100];
  strcpy(check, cstring); // *d = cstring
  strcat(check, cstring); 
  strcat(check, cstring);
  CPPUNIT_ASSERT_STRING_EQUAL(check, *d);

  *b += *a;
  *c = *c + *a;

  CPPUNIT_ASSERT_STRING_EQUAL("blahtblah", *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blahtblah", *c);
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);

  *a = "";
  *a += 4;
  *a -= 4;
  CPPUNIT_ASSERT_EQUAL((size_t)0, a->length());
}

void StringTest :: operatorStarTest(void)
{
  *a = "Test! ";
  *b = *a * 3;
  CPPUNIT_ASSERT_STRING_EQUAL("Test! Test! Test! ", *b);

  const String mytest("Test! ");
  *b = mytest * 3;
  CPPUNIT_ASSERT_STRING_EQUAL("Test! Test! Test! ", *b);
}

void StringTest :: printfTest(void)
{
  int n = 506;
  const char* s = "something";

  a->printf("%s %d", s, n);
  CPPUNIT_ASSERT_STRING_EQUAL("something 506", *a);
}

/*
    a = new String();
    b = new String("blah");
    c = new String(*b);
    d = new String(cstring);
    e = new String(*d);
    f = new String(cstring, 11);
    g = new String('x');
    h = new String(35);
*/

void StringTest :: base64Test(void)
{
  *b = "b";
  *c = *b;
  b->base64Encode();
  CPPUNIT_ASSERT(*b != *c);
  CPPUNIT_ASSERT(*b != "b");
  CPPUNIT_ASSERT_STRING_EQUAL("Yg==", *b);
  b->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("b", *b);

  *b = "bl";
  *c = *b;
  b->base64Encode();
  CPPUNIT_ASSERT(*b != *c);
  CPPUNIT_ASSERT(*b != "bl");
  CPPUNIT_ASSERT_STRING_EQUAL("Ymw=", *b);
  b->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("bl", *b);

  *b = "bla";
  *c = *b;
  b->base64Encode();
  CPPUNIT_ASSERT(*b != *c);
  CPPUNIT_ASSERT(*b != "bla");
  CPPUNIT_ASSERT_STRING_EQUAL("Ymxh", *b);
  b->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("bla", *b);

  *b = "blah";
  *c = *b;
  b->base64Encode();
  CPPUNIT_ASSERT(*b != *c);
  CPPUNIT_ASSERT(*b != "blah");
  CPPUNIT_ASSERT_STRING_EQUAL("YmxhaA==", *b);
  b->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(*c, *b);
  CPPUNIT_ASSERT_STRING_EQUAL("blah", *b);



  d->base64Encode();
  d->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(cstring, *d);

  String eff = String(*f);
  f->base64Encode();
  f->base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(*f, eff);

  /* Test misc lengths of alphabet */
  char *buf = (char*) malloc(100);
  for (int i = 0; i < 100; i++) {
    buf[0] = 0;
    /* Create a buffer of length i */
    for (int k = 0; k < i; k++) {
      char letter[2];
      letter[0] = 'a' + k;
      letter[1] = 0;
      strcat(buf, letter);
    }
    buf[i] = 0;
    String tmpbuf = buf;
    tmpbuf.base64Encode();
//printf("%s -> %s\n", buf, tmpbuf.c_str());
    tmpbuf.base64Decode();
    CPPUNIT_ASSERT_STRING_EQUAL(buf, tmpbuf);
    CPPUNIT_ASSERT_EQUAL((size_t) i, tmpbuf.length());
  }
  free(buf);

  String tmp;

  const char *twentysix = "this is 26 characters long";
  tmp = twentysix;
  tmp.base64Encode();
  tmp.base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(twentysix, tmp);
  CPPUNIT_ASSERT_EQUAL(strlen(twentysix), tmp.length());

  const char *twentynine = "this is 29 characters long ok";
  tmp = twentynine;
  tmp.base64Encode();
  tmp.base64Decode();
  CPPUNIT_ASSERT_STRING_EQUAL(twentynine, tmp);
  CPPUNIT_ASSERT_EQUAL(strlen(twentynine), tmp.length());

  tmp = "";
  tmp.Reserve(255);
  for (unsigned char c = 0; c < 255; c++)
    tmp.append(c);
  String save = String(tmp);
  tmp.base64Encode();
  tmp.base64Decode();
  CPPUNIT_ASSERT_EQUAL((size_t)255, tmp.length());
  CPPUNIT_ASSERT_STRING_EQUAL(save, tmp);
  CPPUNIT_ASSERT_EQUAL(save.length(), tmp.length());
}

#ifdef DISABLED
void StringTest :: encryptTest(void)
{
  b->encrypt(NULL);
  CPPUNIT_ASSERT(*b == *c);
  CPPUNIT_ASSERT(*b == "blah");
  b->encrypt("");
  CPPUNIT_ASSERT(*b == *c);
  CPPUNIT_ASSERT(*b == "blah");

  b->encrypt("doggie");
  CPPUNIT_ASSERT(*b != *c);
  CPPUNIT_ASSERT(*b != "blah");
  String tmp = *b;
  tmp.decrypt("horse");
  CPPUNIT_ASSERT(tmp != *c);
  CPPUNIT_ASSERT(tmp != "blah");
  tmp.encrypt("horse");
  CPPUNIT_ASSERT(tmp == *b);
  tmp.decrypt("doggie");
  CPPUNIT_ASSERT(tmp == "blah");
  CPPUNIT_ASSERT(tmp == *c);
  b->decrypt("doggie");
  CPPUNIT_ASSERT(*b == *c);
  CPPUNIT_ASSERT(*b == "blah");
}

void StringTest :: encryptBase64Test(void)
{
  b->encrypt("doggie");
  b->base64Encode();
  b->base64Decode();
  b->decrypt("doggie");
  CPPUNIT_ASSERT(*b == *c);

  *a = "kGiq0kPEuB7A.3nAGG1D3E..";
  a->decrypt("OeG3yxvQXHq0iw0olaG9mZE8QlmH6vn2");
  a->base64Decode();

  *b = "! uid 1000";
  b->encrypt("OeG3yxvQXHq0iw0olaG9mZE8QlmH6vn2");
  b->base64Encode();
  CPPUNIT_ASSERT(*b == "kGiq0kPEuB7A.3nAGG1D3E..");
  b->base64Decode();
  b->decrypt("OeG3yxvQXHq0iw0olaG9mZE8QlmH6vn2");
  CPPUNIT_ASSERT(*b == "! uid 1000");
}
#endif /* DISABLED */

void StringTest :: substringTest(void)
{
  *a = "Why hello there!";
  String substring(a->substring(4, 5));
  CPPUNIT_ASSERT_STRING_EQUAL("Why hello there!", *a);
  CPPUNIT_ASSERT('h' == substring[0]);
  CPPUNIT_ASSERT_STRING_EQUAL("hello", substring);
  substring += " bryan";
  CPPUNIT_ASSERT_STRING_EQUAL("Why hello there!", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("hello bryan", substring);

  *a = "there goes my reference!";
  CPPUNIT_ASSERT_STRING_EQUAL("there goes my reference!", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("hello bryan", substring);

  *a = "there goes my reference!";
  CPPUNIT_ASSERT_STRING_EQUAL("there goes my reference!", *a);
  substring = a->substring(6, 4);
  *a = "now it is really gone";
  CPPUNIT_ASSERT_STRING_EQUAL("goes", substring);

  *a = "abcdefgh";
  substring = a->substring(3,-2);
  CPPUNIT_ASSERT_STRING_EQUAL("abcdefgh", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("def", substring);

  substring = a->substring(-3, 2);
  CPPUNIT_ASSERT_STRING_EQUAL("fg", substring);

  substring = a->substring(-1,1);
  CPPUNIT_ASSERT_STRING_EQUAL("h", substring);

  substring = a->substring(-1, 5);
  CPPUNIT_ASSERT_STRING_EQUAL("h", substring);

  substring = a->substring(0, 30);
  CPPUNIT_ASSERT_STRING_EQUAL("abcdefgh", substring);

  *a = "This is a test";
  substring = (*a)(-4,4);
  CPPUNIT_ASSERT_STRING_EQUAL("test", substring);

  String substring2(substring);
  CPPUNIT_ASSERT_STRING_EQUAL("test", substring);
  CPPUNIT_ASSERT_STRING_EQUAL("test", substring2);
  CPPUNIT_ASSERT_STRING_EQUAL("This is a test", *a);

  (*a) = "this is just a TEST";
  substring = (*a)(0,4);

  for (size_t i = 0; i < (*a).length(); ++i)
    (*a)[i] = toupper((*a)[i]);

  CPPUNIT_ASSERT_STRING_EQUAL("THIS IS JUST A TEST", (*a));  
  CPPUNIT_ASSERT_STRING_EQUAL("this", substring);

  (*a) = "this is just a TEST";
  substring = (*a)(0,4);

  for (size_t i = 0; i < substring.length(); ++i)
    substring[i] = toupper(substring[i]);

  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("THIS", substring);  

  String replace;

  *b = *a;
  replace = "THIS";
  (*a)(0, 4) = replace;
  CPPUNIT_ASSERT_STRING_EQUAL("THIS is just a TEST", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("THIS", replace);
  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", *b);

  *a = "this is just a TEST";
  *b = *a;
  replace = "THAT";
  (*a)(0, 4) = "THAT";
  CPPUNIT_ASSERT_STRING_EQUAL("THAT is just a TEST", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("THAT", replace);
  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", *b);

  *a = "this is just a TEST";
  *b = *a;
  (*a)(0, 4) = (*b)(15, 4);
  CPPUNIT_ASSERT_STRING_EQUAL("TEST is just a TEST", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", *b);

  *a = "this is just a TEST";
  *b = *a;
  (*a)(0, 4) = (*a)(15, 4);
  CPPUNIT_ASSERT_STRING_EQUAL("TEST is just a TEST", *a);
  CPPUNIT_ASSERT_STRING_EQUAL("this is just a TEST", *b);

  /* this is more of a compile check */
  const String constString("THIS CANNOT BE MODIFIED");
  *a = constString(0, 4);

  constString(0, 4) = "blah"; //Returns a new string

  CPPUNIT_ASSERT_STRING_EQUAL("THIS CANNOT BE MODIFIED", constString);
  CPPUNIT_ASSERT_STRING_EQUAL("THIS", *a);
//  (*a)(-4, 4) = "TEST";
//  CPPUNIT_ASSERT_STRING_EQUAL("This is a TEST", *a);
}

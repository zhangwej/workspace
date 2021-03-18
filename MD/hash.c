��ϣ�㷨�����ⳤ�ȵĶ�����ֵӳ��Ϊ�̶����ȵĽ�С������ֵ�����С�Ķ�����ֵ��Ϊ��ϣֵ����ϣֵ��һ������Ψһ�Ҽ�����յ���ֵ��ʾ��ʽ�����ɢ��һ�����Ķ�������ֻ���ĸö����һ����ĸ�����Ĺ�ϣ����������ͬ��ֵ��Ҫ�ҵ�ɢ��Ϊͬһ��ֵ��������ͬ�����룬�ڼ������ǲ����ܵģ��������ݵĹ�ϣֵ���Լ������ݵ������ԡ�

������ҵ�ʱ��Ч��ΪO(N)�����ַ�Ϊlog2N��B+ TreeΪlog2N����Hash������ҵ�ʱ��Ч��ΪO(1)��

��Ƹ�Ч�㷨������Ҫʹ��Hash�����������Ĳ����ٶ����κα���㷨�޷�����ģ�Hash����Ĺ���ͳ�ͻ�Ĳ�ͬʵ�ַ�����Ч�ʵ�Ȼ��һ����Ӱ�죬Ȼ ��Hash������Hash��������ĵĲ��֣������Ǽ���������ʹ�õ����ַ���Hash����ʵ�֣�ͨ���Ķ���Щ���룬���ǿ�����Hash�㷨��ִ��Ч�ʡ���ɢ�ԡ��ռ������ʵȷ����бȽ���̵��˽⡣

����ֱ���ܼ�����������г��ֵ��ַ���Hash������

��PHP�г��ֵ��ַ���Hash����

static unsigned long hashpjw(char *arKey, unsigned int nKeyLength)
{
unsigned long h = 0, g;
char *arEnd=arKey+nKeyLength; 

while (arKey < arEnd) {
h = (h << 4) + *arKey++;
if ((g = (h & 0xF0000000))) {
h = h ^ (g >> 24);
h = h ^ g;
}
}
return h;
}

��OpenSSL�г��ֵ��ַ���Hash����

unsigned long lh_strhash(char *str)
{
int i,l;
unsigned long ret=0;
unsigned short *s; 

if (str == NULL) return(0);
l=(strlen(str)+1)/2;
s=(unsigned short *)str; 

for (i=0; i
ret^=(s[i]<<(i&0x0f));
return(ret);
} 

/* The following hash seems to work very well on normal text strings 
* no collisions on /usr/dict/words and it distributes on %2^n quite 
* well, not as good as MD5, but still good. 
*/
unsigned long lh_strhash(const char *c)
{
unsigned long ret=0;
long n;
unsigned long v;
int r; 

if ((c == NULL) || (*c == '\0'))
return(ret);
/*
unsigned char b[16]; 
MD5(c,strlen(c),b); 
return(b[0]|(b[1]<<8)|(b[2]<<16)|(b[3]<<24)); 
*/ 

n=0x100;
while (*c)
{
v=n|(*c);
n+=0x100;
r= (int)((v>>2)^v)&0x0f;
ret=(ret(32-r));
ret&=0xFFFFFFFFL;
ret^=v*v;
c++;
} 

return((ret>>16)^ret);
}

��MySql�г��ֵ��ַ���Hash����

#ifndef NEW_HASH_FUNCTION 

/* Calc hashvalue for a key */
static uint calc_hashnr(const byte *key,uint length)
{
register uint nr=1, nr2=4; 

while (length--)
{
nr^= (((nr & 63)+nr2)*((uint) (uchar) *key++))+ (nr << 8);
nr2+=3;
} 

return((uint) nr);
} 

/* Calc hashvalue for a key, case indepenently */
static uint calc_hashnr_caseup(const byte *key,uint length)
{
register uint nr=1, nr2=4; 

while (length--)
{
nr^= (((nr & 63)+nr2)*((uint) (uchar) toupper(*key++)))+ (nr << 8);
nr2+=3;
} 

return((uint) nr);
}
#else
/* 
* Fowler/Noll/Vo hash 
* 
* The basis of the hash algorithm was taken from an idea sent by email to the 
* IEEE Posix P1003.2 mailing list from Phong Vo (kpv@research.att.com) and 
* Glenn Fowler (gsf@research.att.com). Landon Curt Noll (chongo@toad.com) 
* later improved on their algorithm. 
* 
* The magic is in the interesting relationship between the special prime 
* 16777619 (2^24 + 403) and 2^32 and 2^8. 
* 
* This hash produces the fewest collisions of any function that we've seen so 
* far, and works well on both numbers and strings. 
*/
uint calc_hashnr(const byte *key, uint len)
{
const byte *end=key+len;
uint hash; 

for (hash = 0; key < end; key++)
{
hash *= 16777619;
hash ^= (uint) *(uchar*) key;
} 

return (hash);
} 

uint calc_hashnr_caseup(const byte *key, uint len)
{
const byte *end=key+len;
uint hash; 

for (hash = 0; key < end; key++)
{
hash *= 16777619;
hash ^= (uint) (uchar) toupper(*key);
} 

return (hash);
}
#endif

Mysql�ж��ַ���Hash�����������˴�Сд

����һ�������ַ���Hash����

unsigned int hash(char *str)
{
register unsigned int h;
register unsigned char *p; 

for(h=0, p = (unsigned char *)str; *p ; p++)
h = 31 * h + *p; 

return h;
}
#include <iostream>
#include <memory>

using namespace std;

class Image
{

   bool original = true;

protected:
   Image(const Image&) = default;
public:
   Image() = default;
   void modifier() { original = false; }
   bool est_modifier() const { return !original; }
   virtual Image* cloner() const = 0;
   virtual void Dessiner() const = 0;
   virtual ~Image() = default;
};

class Jpeg :public Image
{
protected:
   Jpeg(const Jpeg&) = default;
public:
   Jpeg() = default;
   Jpeg *cloner() const override
   {
      return new Jpeg{*this};
   }
   void Dessiner() const override
   {
      cout << "JPeg" << endl;
   }
};

class Png : public Image
{
protected:
   Png(const Png&) = default;
public:
   Png() = default;
   Png *cloner() const override
   {
      return new Png{ *this };
   }
   void Dessiner() const override
   {
      cout << "Png" << endl;
   }
};

unique_ptr<Image> ModifMaybe(unique_ptr<Image> p)
{
   unique_ptr<Image> bak{ p->cloner() };

   // modifier *p ... omis pour fin de simplicité

   cout << "Voulez-vous conserver les modifs? ";
   char c;
   while (cin >> c && c != 'O' && c != 'N')
      cout << "Voulez-vous conserver les modifs? ";

   // si l'usager veut garder les modifs, on scrappe le backup
   //sinon on scrappe p
   if (c == 'N')
      swap(p, bak);
   return p;
}

int main()
{
   unique_ptr<Image> p{ new Png };
   p = ModifMaybe(move(p));
   p->Dessiner();
   if (p->est_modifier())
   {
      cout << "(Version modifier)" << endl;
   }
   else {
      cout << "(Version original)" << endl;
   }
}
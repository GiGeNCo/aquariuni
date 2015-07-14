# Aquariuni
Smart Aquarium Project for IliaUni.
პროექტი წარმოადგენს ჭკვიან ტერარიუმს, რომელციც ავტომატურად უქმნის იდეალურ გარემო-პირობებს მასში მოთავსებულ მცენარეს ან/და ცხოველს.

### კომპილაცია
კომპილაცია შესაძლებელია Makefile-ით ან/და build სკრიპტით.

მეიქფაილის შემთხვევაში:
```
git clone https://github.com/kala13x/aquariuni.git
cd aquariuni/src
make
```
სკრიპტის შემთხვევაში:
```
git clone https://github.com/kala13x/aquariuni.git
cd aquariuni
chmod +x build.sh
./build.sh
```
სკრიპტი დაბულდავს მთლიან პროექტს და დააინსტალირებს მას თქვენს სისტემაზე, ასევე გამშვებ ფაილს გადააკოპირებს '/etc/init.d' დირექტორიაში რადგან სისტემის ჩართვისას (startup) ავტომატურად მოხდეს პროგრამის გაშვება.

### ბიბლიოთეკები
პროექტის დასაკომპირებლად, საჭიროა პლატფორმაზე დაინსტალირებული იყოს Raspberi Pi-ს თან მომუშავე ბიბლიოთეკა writingPi.

```
sudo apt-get install git-core
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
```

### პროცესი
- [x] ტენიანობის სენსორის დრაივერი
- [x] ტემპერატურის სენსორის დრაივერი
- [x] ეკრანის დრაივერი
- [x] რელეების მართვის დრაივერი

### კავშირი
დივაისების პინებით რასპბერიზე დაერთების სქემები და სურათები შეგიძლიათ ნახოთ ამავე პროექტის img დირექტორიაში. 

### პროდუქტის სურათი
<p align="center">
  <img src="https://raw.githubusercontent.com/kala13x/aquariuni/master/img/product.png" alt="Product"/>
</p>

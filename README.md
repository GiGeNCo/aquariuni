# Aquariuni
Smart Aquarium Project for IliaUni

### კომპილაცია
კომპილაცია შესაძლებელია Makefile-ით

```
git clone git@github.com:kala13x/aquariuni.git
cd aquariuni/src
make
```

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
- [ ] კამერის დრაივერი (პროცესშია)


### ეკრანის პინების დაერთება რასპბერიზე
<p align="center">
  <img src="https://raw.githubusercontent.com/kala13x/aquariuni/master/img/lcd2pi.png" alt="PCDPins"/>
</p>

### ტენიანობის და წნევის სენსორის დაერთება რასპბერიზე
<p align="center">
  <img src="https://raw.githubusercontent.com/kala13x/aquariuni/master/img/dht11pi.jpg" alt="DHTPins"/>
</p>
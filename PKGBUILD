
# Maintainer: Steven Mattera <me@stevenmattera.com>
pkgname=switch-simple-ini-parser
pkgver=1.0.0
pkgrel=1
pkgdesc='A very simple INI parser written in C++.'
arch=('any')
license=('custom')
url='https://github.com/AtlasNX/SimpleIniParser'
options=(!strip libtool staticlibs)
makedepends=('switch-pkg-config' 'devkitpro-pkgbuild-helpers')
source=("https://github.com/AtlasNX/SimpleIniParser/archive/v${pkgver}.tar.gz")

sha256sums=('SKIP')

build() {
  cd SimpleIniParser-$pkgver

  source /opt/devkitpro/switchvars.sh

  make  
}

package() {
  cd SimpleIniParser-$pkgver

  source /opt/devkitpro/switchvars.sh

  make DESTDIR="$pkgdir" install
  rm $pkgdir$PORTLIBS_PREFIX/LICENSE
}

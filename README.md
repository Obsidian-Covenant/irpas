# irpas

## Modernization Covenant

This is a refactored and modernized edition of **irpas**, an Internetwork Routing Protocol Attack Suite.

Key changes:

- ✅ Fixed errors and warnings caused by old libraries
- ✅ Refactored code to be used with latest gcc version

### Installation

#### Dependencies

Build dependencies:
```
gcc
```

Runtime dependencies:
```
libpcap libtirpc
```

#### From source

```bash
git clone https://github.com/Obsidian-Covenant/irpas.git
cd irpas
make
sudo make install
```
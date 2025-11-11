## SuperTree
**SuperTree** is a fast and powerful command-line tool like GNU Tree.
It shows the directory structure of files and folders in a beautiful tree format.
It also supports sorting by size, showing file sizes in KB, MB, GB or TB, and displaying only directories if needed.

## Features
- Shows folder and file structure in a tree view

- Shows sizes in **bytes**, **KB**, **MB**, **GB**, or **TB**

- Sort by total size using the `-S` flag

- Show only directories with the `--dirs-only` flag

- Show sizes next to each file or folder using `--size`

- Limit the depth level with `-L`

- Colored output for easy reading

- JSON output option

## Note

Before building **SuperTree**, make sure the required build tools are installed on your system.

**Debian/Ubuntu/Kali/parrot:**
```bash
sudo apt install build-essential -y
```
**Arch/BlackArch/Manjaro:**
```bash
sudo pacman -Sy base-devel --noconfirm
```
**Fedora/RHEL/CentOS:**
```bash
sudo dnf groupinstall "Development Tools" -y
```
**Termux:**
```bash
pkg install clang make -y
```
These packages ensure that **gcc** or **clang** and **make** are available for compiling and building **SuperTree**.

## Installation
1. **Clone the repository**
```bash
git clone https://github.com/s-r-e-e-r-a-j/SuperTree.git
```
2. **Go to the SuperTree directory**
```bash
cd SuperTree
```
3. **Build the program**
```bash
make
```
### Installation Paths
**For Linux:**

Move the binary to `/usr/local/bin`:
```bash
sudo mv supertree /usr/local/bin/
```
Now you can run it anywhere:
```bash
supertree
```
**For Termux:**

Move the binary to `$PREFIX/bin`:
```bash
mv supertree $PREFIX/bin/
```
Now you can use it in Termux:
```bash
supertree
```
## Usage
```bash
# supertree without any arguments will print the structure of the current working directory
supertree

# supertree with options and directory/path
supertree [options] [directory]

```
### Options

| Option       | Description                  |
|--------------|------------------------------|
| `-L <num>`   | Limit tree depth             |
| `--dirs-only`| Show only directories        |
| `--size`     | Show sizes in readable units |
| `-S`         | Sort by total size           |
| `--json`     | Output in JSON format        |

## Examples

**Show current directory:**
```bash
supertree
```

**Show with sizes:**
```bash
supertree --size
```

**Sort by total size:**
```bash
supertree -S --size
```

**Only directories:**
```bash
supertree --dirs-only
```

**Limit to 2 levels(only shows folders and files inside subfolders up to 2 levels):**
```bash
supertree -L 2
```

**show a specific path:**
```bash
supertree /home/user/projects
```
**show a specific path with size and size sorting:**
```bash
supertree -S --size /var/log
```
**show output as JSON:**
```bash
supertree --json /home/user/Documents
```
**show a path limited to 2 levels deep (only shows folders and files inside subfolders up to 2 levels):**
```bash
supertree -L 2 /etc
```

## License
This project is licensed under the MIT License

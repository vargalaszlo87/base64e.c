# base64e.c
Base64 encoder in C without external library. 

## Notice
Workd with 7bit ASCII, does not support UTF-8.

## Usage
It's very simply:
```C
char *enc = base64Encode("Follow the white rabbit...");
```

## Example
```C
int main(int argc, char *argv[]) {
	char *msg = "Follow the white rabbit...";
	char *enc = base64Encode(msg);
	printf ("%s", enc);
	return 0;
}
```

## License
The project is released under the [MIT license](http://www.opensource.org/licenses/MIT).

## Contact
The project's website is located at https://github.com/vargalaszlo87/base64e.c

My personal website is located at http://vargalaszlo.com/index.php?q=c_base64e

Author: Laszlo, Varga (varga.laszlo.drz@gmail.com)

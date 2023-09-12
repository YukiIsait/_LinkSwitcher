# Link Switcher

The Link Switcher allows changing the target of directory links by command-line arguments, such as switching Java versions.

## Usage

In the following steps, the JDK environment located at `D:\Environment\Java` will be used for demonstration purposes.

```
D:\Environment\Java
├─OpenJDK_11.0.18
├─OpenJDK_17.0.6
├─OpenJDK_19.0.2
└─OpenJDK_8.362
```

1. Copy `LinkSwitcher.exe` to this directory and rename it to `swj.exe` (or to any name you prefer).

2. Create an empty directory named `Current`, and add `D:\Environment\Java` and `D:\Environment\Java\Current` to the `PATH` environment variable.

3. Create a text file named `swj.txt` (same as Step 1) using `UTF-16 LE` encoding. After these 3 steps, the contents of the directory are as follows:

```
D:\Environment\Java
├─OpenJDK_11.0.18
├─OpenJDK_17.0.6
├─OpenJDK_19.0.2
├─OpenJDK_8.362
├─Current
├─swj.exe
└─swj.txt
```

4. Edit the `swj.txt` file to include labels and paths. The content of the file is as follows:

```
j8: OpenJDK_8.362
j11: OpenJDK_11.0.18
j17: OpenJDK_17.0.6
j19: OpenJDK_19.0.2
```

5. To switch to Java 8, run `swj j8` in the command line.

```
swj j8
```

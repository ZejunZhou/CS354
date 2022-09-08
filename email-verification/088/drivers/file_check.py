import sys



if __name__ == "__main__":
    contents = ""
    with open("diff_output.txt") as f:
        contents = f.read()

    if len(contents) > 0:
        print("ERROR: Found differing output:")
        print(contents)
        sys.exit(1)


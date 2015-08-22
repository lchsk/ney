from tester.loader import Loader
from tester.parser import Parser

# Settings

UNITTEST_PATH = '../unittest/'
EXTENSIONS = ('_report', '.optrpt')

# ---

def main():
    loader = Loader(UNITTEST_PATH, EXTENSIONS)
    parser = Parser(loader)

if __name__ == '__main__':
    main()

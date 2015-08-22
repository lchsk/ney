from os import listdir
from os.path import isfile, join
import re

class Loader(object):
    def __init__(self, path, extensions):
        self.path = path
        self.extentions = extensions

        self.reports = []
        self.load_()

    def load_(self):
        allfiles = [ f for f in listdir(self.path) if isfile(join(self.path, f)) ]

        for f in allfiles:
            for ext in self.extentions:
                if re.match(r'.*' + ext + '$', f):
                    self.reports.append(f)

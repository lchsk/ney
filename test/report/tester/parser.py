import re
from colors import *

class Parser(object):
    def __init__(self, loader):
        self.loader = loader
        self.error_c = 0
        self.success_c = 0

        self.parse_all_()
        self.print_stats_()

    def parse_all_(self):
        for f in self.loader.reports:
            self.parse_(f)

    def print_stats_(self):
        print str(len(self.loader.reports)) + ' reports analysed'
        print str(self.success_c) + ' / ' + str(self.success_c + self.error_c) + ' (' + str(round(float(self.success_c) / float(self.success_c + self.error_c) * 100)) + ' %)'

    def get_filename_(self, line):
        # path only: [a-z\\/\._]+\.cpp
        m = re.findall(r'[a-z\\/\._]+\.cpp\([0-9,]+\)', line)

        if m:
            return m[0]
        else:
            return False

    def parse_loop_vec_(self, line):

        show, positive, text = False, False, ''

        if 'loop was not vectorized' in line.lower():
            show = True
            positive = False
            text = line
        elif 'was vectorized' in line.lower():
            show = True
            positive = True
            text = line

        return show, positive, text

    def parse_(self, path):

        f = open(self.loader.path + path)
        source_path = False


        for line in f:
            result = self.get_filename_(line)

            if result:
                source_path = result

            show, positive, text = self.parse_loop_vec_(line)

            if show:
                if positive:
                    self.success_c += 1
                    printc('SUCCESS ' + str(self.success_c) + ' in ' + str(source_path) + ':', COLORS.GREEN)
                    printc(text.strip(), COLORS.GREEN)
                    print '\n'
                elif source_path:
                    self.error_c += 1
                    printc('ERROR ' + str(self.error_c) + ' in ' + str(source_path) + ':', COLORS.YELLOW)
                    printc(text.strip(), COLORS.RED)
                    print '\n'



        f.close()

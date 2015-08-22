import re
from colors import *

class Parser(object):
    def __init__(self, loader):
        self.loader = loader
        self.error_c = 0
        self.success_c = 0
        self.issue_c = 0

        self.parse_all_()
        self.print_stats_()

    def parse_all_(self):
        for f in self.loader.reports:
            self.parse_(f)

    def print_stats_(self):
        print str(len(self.loader.reports)) + ' reports analysed'
        if self.success_c + self.error_c > 0:
            print str(self.success_c) + ' / ' + str(self.success_c + self.error_c) + ' (' + str(round(float(self.success_c) / float(self.success_c + self.error_c) * 100)) + ' %)'

    def get_filename_(self, line):
        # path only: [a-z\\/\._]+\.cpp
        m = re.findall(r'[a-z\\/\._]+\.[a-z]{3}\([0-9,]+\)', line)

        if m:
            return m[0]
        else:
            return False

    def parse_loop_vec_(self, line):
        '''Checks for comments regarding loop vectorisation'''

        show, positive, text = False, 0, ''

        line_ = line.lower()

        if 'vectorization possible but seems inefficient' in line_:
            show = True
            positive = 1
            text = line
        elif 'loop was not vectorized' in line_:
            show = True
            positive = 0
            text = line
        elif 'was vectorized' in line_:
            show = True
            positive = 1
            text = line

        return show, positive, text

    def parse_aligned_access_(self, line):
        '''Checks for comments regarding aligned access to variables'''

        show, positive, text = False, 0, ''

        line_ = line.lower()

        if 'has unaligned access' in line_:
            show = True
            positive = 0
            text = line
        elif 'has aligned access' in line_:
            show = True
            positive = 1
            text = line

        return show, positive, text

    def parse_(self, path):

        f = open(self.loader.path + path)
        source_path = False


        for line in f:
            result = self.get_filename_(line)

            if result:
                source_path = result

                if '_unittest' in source_path:
                    source_path = -1

            show, positive, text = self.parse_loop_vec_(line)
            a_show, a_positive, a_text = self.parse_aligned_access_(line)

            # Loop vectorisation

            if show and source_path != -1:
                if positive == 1:
                    self.success_c += 1
                    printc('SUCCESS ' + str(self.success_c) + ' in ' + str(source_path) + ':', COLORS.GREEN)
                    printc(text.strip(), COLORS.GREEN)
                    print '\n'
                elif positive == -1:
                    self.issue_c += 1
                    printc('ISSUE ' + str(self.issue_c) + ' in ' + str(source_path) + ':', COLORS.YELLOW)
                    printc(text.strip(), COLORS.YELLOW)
                    print '\n'
                elif positive == 0:
                    self.error_c += 1
                    printc('ERROR ' + str(self.error_c) + ' in ' + str(source_path) + ':', COLORS.YELLOW)
                    printc(text.strip(), COLORS.RED)
                    print '\n'

            # Aligned access

            if a_show:
                if a_positive == 1:
                    self.success_c += 1
                    printc('SUCCESS ' + str(self.success_c) + ' in ' + str(source_path) + ':', COLORS.GREEN)
                    printc(a_text.strip(), COLORS.GREEN)
                    print '\n'
                elif a_positive == 0:
                    self.error_c += 1
                    printc('ERROR ' + str(self.error_c) + ' in ' + str(source_path) + ':', COLORS.YELLOW)
                    printc(a_text.strip(), COLORS.RED)
                    print '\n'

        f.close()

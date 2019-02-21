#!c:\Python26\pythonw.exe

# --------------------------------------------------------------------
#  Demo script for nesting problem
#
#  Author: Shunji Umetani <umetani@ist.osaka-u.ac.jp>
#  Date: 2009/08/11
# --------------------------------------------------------------------

# import modules -----------------------------------------------------
from Tkinter import *
from Tkinter import _flatten
from time import *
import tkFileDialog
import copy

# constant -----------------------------------------------------------
default_window_ratio = 0.9
default_view_interval = 50
WINDOW_MARGIN = 20

# --------------------------------------------------------------------
# classes
# --------------------------------------------------------------------

# --------------------------------------------------------------------
# piece
class Piece():
    def __init__(self):
        self.mode_num = 0  # number of modes
        self.shape_list = []  # list of shapes

# --------------------------------------------------------------------
# shape
class Shape():
    def __init__(self):
        self.vertex_num = 0  # number of vertices
        self.area = 0  # area
        self.x_list = []  # list of x-coordinates of vertices
        self.y_list = []  # list of y-coordinates of vertices

# --------------------------------------------------------------------
# solution
class Solution():
    def __init__(self):
        self.strip_width = 0.0  # strip width
        self.utilization = 0.0  # utilization of solution
        self.move_num = 0 # number of moved pieces
        self.location_list = []  # list of locations of moved pieces

# --------------------------------------------------------------------
# location
class Location():
    def __init__(self):
        self.idx = None  # index of piece
        self.placement = False  # placement flag of piece
        self.mode = None  # mode index of piece
        self.x = 0.0  # x-coordinate of piece
        self.y = 0.0  # y-coordinate of piece
        self.overlap = False  # overlap flag of piece

# --------------------------------------------------------------------
# demo
class Demo(Frame):

    # initialize ---------------------------------
    def __init__(self, master=None):
        Frame.__init__(self, master)
        # initialize widgets
        self.grid()
        self.create_widgets()
        self.master.title("Nesting problem demo program")
        # initialize input data
        self.strip_height = 0.0
        self.piece_list = []
        self.piece_num = 0
        self.solution_list = []
        self.solution_num = 0
        # initialize state
        self.pause_flag = True
        self.draw_flag = False
        self.fs_draw_flag = False
        self.fs_flag = False
        self.cnt = 0
        # initialize size of windows
        self.canvas_width = 0.0
        self.canvas_height = 0.0
        self.scale = 0.0
        # initialize figure_list
        self.figure_list1 = []
        self.container1 = None
        self.figure_list2 = []
        self.container2 = None
        # initialize complete solution
        self.complete_solution = None

    # create widgets -----------------------------
    def create_widgets(self):
        # canvas title1
        self.title1 = Label(self, font=('Helvetica', '16'), text='Current solution')
        self.title1.grid(row=0, column=0, columnspan=3, padx=5, pady=5, sticky=E+W)
        # canvas title2
        self.title2 = Label(self, font=('Helvetica', '16'), text='Feasible solution')
        self.title2.grid(row=0, column=3, columnspan=3, padx=5, pady=5, sticky=E+W)
        # canvas1 
        self.canvas1 = Canvas(self, bg='white')
        self.canvas1.grid(row=1, column=0, columnspan=3, padx=5, pady=5)
        # canvas1 
        self.canvas2 = Canvas(self, bg='white')
        self.canvas2.grid(row=1, column=3, columnspan=3, padx=5, pady=5)        
        # data label1
        self.data_label1 = Label(self, font=('Helvetica', '16'))
        self.data_label1.grid(row=2, column=0, columnspan=3, padx=5, pady=5, sticky=E+W)
        # data label2
        self.data_label2 = Label(self, font=('Helvetica', '16'))
        self.data_label2.grid(row=2, column=3, columnspan=3, padx=5, pady=5, sticky=E+W)
        # view interval
        self.view_interval = IntVar()
        self.view_interval.set(default_view_interval)
        self.view_interval_slider = Scale(self, label='View interval', orient=HORIZONTAL, from_=0, to=100, tickinterval=10, resolution=10, font=('Helvetica', '12'), variable=self.view_interval)
        self.view_interval_slider.grid(row=3, column=0, columnspan=3, padx=5, pady=5, sticky=E+W)
        # window size
        self.window_ratio = DoubleVar()
        self.window_ratio.set(default_window_ratio)
        self.window_size_slider = Scale(self, label='Window size', orient=HORIZONTAL, from_=0.1, to=0.9, tickinterval=0.1, resolution=0.1, font=('Helvetica', '12'), variable=self.window_ratio)
        self.window_size_slider.grid(row=3, column=3, columnspan=3, padx=5, pady=5, sticky=E+W)
        # load
        self.load_button = Button(self, text='Load', command=self.load_file)
        self.load_button.grid(row=4, column=0, padx=5, pady=5, sticky=E+W)
        # start
        self.start_button = Button(self, text='Start', state=DISABLED, command=self.start_movie)
        self.start_button.grid(row=4, column=1, padx=5, pady=5, sticky=E+W)
        # pause
        self.pause_button = Button(self, text='Pause', state=DISABLED, command=self.toggle_pause)
        self.pause_button.grid(row=4, column=2, padx=5, pady=5, sticky=E+W)
        # step
        self.step_button = Button(self, text='Step', state=DISABLED, command=self.step_movie)
        self.step_button.grid(row=4, column=3, padx=5, pady=5, sticky=E+W)
        # reset
        self.reset_button = Button(self, text='Reset', state=DISABLED, command=self.reset_movie)
        self.reset_button.grid(row=4, column=4, padx=5, pady=5, sticky=E+W)
        # quit
        self.quit_button = Button(self, text='Quit', command=self.quit)
        self.quit_button.grid(row= 4, column=5, padx=5, pady=5, sticky=E+W)
        
    # load file ----------------------------------
    def load_file(self):
        # initialize data
        self.init_data()
        # get file name
        self.filename = tkFileDialog.askopenfilename()
        #print "filename=", self.filename
        read_st = time()
        # open file 
        input_file = open(self.filename,"r")
        # read file into buffer
        buf = input_file.read()
        # split buffer data into lines
        line_list = buf.split('\n')
        line_num = len(line_list)
        # scan data
        self.scan_data(line_list, line_num)
        # delete buffer and line_list
        del buf
        del line_list
        # close file
        input_file.close()
        read_fn = time()
        # print data
        #print "strip_height= ", self.strip_height
        #print "piece_num= ", self.piece_num
        #print "solution_num= ", self.solution_num
        #print "read time= ", read_fn - read_st
        #self.print_data()
        # calculate canvas_size
        self.calc_canvas_size()
        # resize canvas height and width
        self.canvas1.configure(height=self.canvas_height+WINDOW_MARGIN * 2,width=self.canvas_width+WINDOW_MARGIN * 2)
        self.canvas2.configure(height=self.canvas_height+WINDOW_MARGIN * 2,width=self.canvas_width+WINDOW_MARGIN * 2)
        # initialize state
        self.init_state()
        # set state of buttons
        self.pause_button.configure(state=DISABLED)
        self.start_button.configure(state=NORMAL)
        self.reset_button.configure(state=NORMAL)
        self.step_button.configure(state=NORMAL)
        self.view_interval_slider.configure(state=NORMAL)
        self.window_size_slider.configure(state=NORMAL)
        # draw initial solution
        self.draw_current_solution()
        # draw feasible solution
        if self.fs_flag == True:
            self.draw_feasible_solution()
        
    # start movie -------------------------------
    def start_movie(self):
        # set state as pause
        self.pause_flag = False
        # set state of buttons
        self.pause_button.configure(state=NORMAL)
        self.start_button.configure(state=DISABLED)
        self.reset_button.configure(state=DISABLED)
        self.step_button.configure(state=DISABLED)
        self.view_interval_slider.configure(state=NORMAL)
        self.window_size_slider.configure(state=DISABLED)
        # run movie
        self.run_movie()

    # reset movie --------------------------------
    def reset_movie(self):
        # initialize state
        self.init_state()
        # calculate canvas_size
        self.calc_canvas_size()
        # resize canvas height and width
        self.canvas1.configure(height=self.canvas_height+WINDOW_MARGIN * 2,width=self.canvas_width+WINDOW_MARGIN * 2)
        self.canvas2.configure(height=self.canvas_height+WINDOW_MARGIN * 2,width=self.canvas_width+WINDOW_MARGIN * 2)
        # change state of buttons
        self.pause_button.configure(state=DISABLED)
        self.start_button.configure(state=NORMAL)
        self.reset_button.configure(state=NORMAL)
        self.step_button.configure(state=NORMAL)
        self.view_interval_slider.configure(state=NORMAL)
        self.window_size_slider.configure(state=NORMAL)
        # draw current solution
        self.draw_current_solution()
        # draw feasible solution
        if self.fs_flag == True:
            self.draw_feasible_solution()
            
    # run movie ---------------------------------
    def run_movie(self):
        while self.pause_flag == False:
            # wait a specified interval
            self.after(self.view_interval.get())
            # increase counter
            self.cnt += 1
            if self.cnt < self.solution_num:
                # update complete solution
                self.update_complete_solution()
                # check feasible
                self.fs_flag = self.check_feasible()
                # draw current solution
                self.draw_current_solution()
                # draw feasible solution
                if self.fs_flag == True:
                    self.draw_feasible_solution()
            else:
                # change state of buttons
                self.start_button.configure(state=DISABLED)
                self.pause_button.configure(state=DISABLED)
                self.reset_button.configure(state=NORMAL)
                self.step_button.configure(state=DISABLED)
                self.view_interval_slider.configure(state=NORMAL)
                self.window_size_slider.configure(state=NORMAL)
                break
    
    # step movie ---------------------------------
    def step_movie(self):
        if self.pause_flag == True:
            # increase counter
            self.cnt += 1
            if self.cnt < self.solution_num:
                # update complete solution
                self.update_complete_solution()
                # check feasible
                self.fs_flag = self.check_feasible()
                # draw current solution
                self.draw_current_solution()
                # draw feasible solution
                if self.fs_flag == True:
                    self.draw_feasible_solution()
            else:
                # change state of buttons
                self.start_button.configure(state=DISABLED)
                self.pause_button.configure(state=DISABLED)
                self.reset_button.configure(state=NORMAL)
                self.step_button.configure(state=DISABLED)
                self.view_interval_slider.configure(state=NORMAL)
                self.window_size_slider.configure(state=NORMAL)
                    
    # toggle pause -------------------------------
    def toggle_pause(self):
        if self.pause_flag == False:
            # change state as pause
            self.pause_flag = True
            # change state of buttons
            self.pause_button.configure(state=DISABLED)
            self.start_button.configure(state=NORMAL)
            self.reset_button.configure(state=NORMAL)
            self.step_button.configure(state=NORMAL)
            self.view_interval_slider.configure(state=NORMAL)
            self.window_size_slider.configure(state=NORMAL)
        else:
            # change state as run
            self.pause_flag = False
            # change state of buttons
            self.pause_button.configure(state=NORMAL)
            self.start_button.configure(state=DISABLED)
            self.reset_button.configure(state=DISABLED)
            self.step_button.configure(state=DISABLED)
            self.view_interval_slider.configure(state=NORMAL)
            self.window_size_slider.configure(state=DISABLED)
            # run movie
            self.run_movie()
            
    # init data ----------------------------------
    def init_data(self):
        # initialize input data
        self.strip_height = 0.0
        self.piece_list = []
        self.piece_num = 0
        self.solution_list = []
        self.solution_num = 0
        # initialize size of windows
        self.canvas_width = 0.0
        self.canvas_height = 0.0
        self.scale = 0.0

    # init state ---------------------------------
    def init_state(self):
        # delete all object on canvas
        self.canvas1.delete(self.container1)
        for figure in self.figure_list1:
            self.canvas1.delete(figure)
        self.canvas2.delete(self.container2)
        for figure in self.figure_list2:
            self.canvas2.delete(figure)            
        # initialize state
        self.pause_flag = True
        self.draw_flag = False
        self.fs_draw_flag = False        
        self.cnt = 0      
        # initialize figure_list
        self.figure_list1 = []
        self.container1 = None
        self.figure_list2 = []
        self.container2 = None
        # initialize complete solution
        self.complete_solution = copy.deepcopy(self.solution_list[self.cnt])
        # initialize fs_flag
        self.fs_flag = self.check_feasible()

    # scan data ----------------------------------
    def scan_data(self, line_list, line_num):
        # initialize indicator
        line_idx = 0
        # scan strip_height
        line = line_list[line_idx]
        line_idx += 1
        self.strip_height = float((line.split())[1])
        # scan piece_num
        line = line_list[line_idx]
        line_idx += 1
        self.piece_num = int((line.split())[1])
        # scan piece_list
        for i in range(self.piece_num):
            # initialize piece instance
            piece = Piece()
            # scan mode_num
            line = line_list[line_idx]
            line_idx += 1
            piece.mode_num = int((line.split())[1])
            # scan shape_list
            for j in range(piece.mode_num):
                # initialize shape instance
                shape = Shape()
                # scan vertex_num
                line = line_list[line_idx]
                line_idx += 1
                shape.vertex_num = int((line.split())[1])
                # scan area
                line = line_list[line_idx]
                line_idx += 1
                shape.area = float((line.split())[1])
                # scan coordinates of vertices
                for k in range(shape.vertex_num):
                    line = line_list[line_idx]
                    line_idx += 1
                    x = float((line.split())[0])
                    y = float((line.split())[1])
                    shape.x_list.append(x)
                    shape.y_list.append(y)
                # append shape instance to shape_list
                piece.shape_list.append(shape)
            # append piece object to piece_list
            self.piece_list.append(piece)    
        # scan solution_list
        while line_list[line_idx] != "":
            # initialize solution instance
            solution = Solution()
            # scan strip_width
            line = line_list[line_idx]
            line_idx += 1
            solution.strip_width = float((line.split())[1])
            # scan utilization
            line = line_list[line_idx]
            line_idx += 1
            solution.utilization = float((line.split())[1])
            # scan number of moved pieces
            line = line_list[line_idx]
            line_idx += 1
            solution.move_num = int((line.split())[1])            
            # scan location_list
            for i in range(solution.move_num):
                # initialize location instance
                location = Location()
                # scan location
                line = line_list[line_idx]
                line_idx += 1
                items = line.split()
                location.idx = int(items[0])
                location.placement = int(items[1])
                location.mode = int(items[2])
                location.x = float(items[3])
                location.y = float(items[4])
                location.overlap = int(items[5])
                # append location instance to location_list
                solution.location_list.append(location)
            # append solution instance to solution_list
            self.solution_list.append(solution)
            # increase number of solutions
            self.solution_num += 1

    # print data ---------------------------------
    def print_data(self):
        # print strip_height
        print ("h= ", self.strip_height)
        # print piece_list
        print ("n= ", self.piece_num)
        for piece in self.piece_list:
            print ("m= ", piece.mode_num)
            for shape in piece.shape_list:
                print ("v= ", shape.vertex_num)
                print ("a= ", shape.area)
                for k in range(shape.vertex_num):
                    print (shape.x_list[k], shape.y_list[k])
        # print solution_list
        for solution in self.solution_list:
            print ("w= ", solution.strip_width)
            print ("u= ", solution.utilization)
            print ("n= ", solution.move_num)
            for location in solution.location_list:
                print (location.idx, location.placement, location.mode, location.x, location.y, location.overlap)

    # calculate canvas_size ----------------------
    def calc_canvas_size(self):
        # get screen height and width
        screen_height = self.winfo_screenheight()
        screen_width = self.winfo_screenwidth()
        # set maximum canvas size
        max_canvas_height = screen_height * self.window_ratio.get() * 0.8
        max_canvas_width = screen_width * self.window_ratio.get() / 2.0
        # find max_strip_width
        max_strip_width = 0.0
        for i in range(self.solution_num):
            if self.solution_list[i].strip_width > max_strip_width:
                max_strip_width = self.solution_list[i].strip_width
        # set scale factor and canvas size
        height_scale = max_canvas_height / self.strip_height
        width_scale = max_canvas_width / max_strip_width
        if height_scale < width_scale:
            self.scale = height_scale
            self.canvas_height = max_canvas_height
            self.canvas_width = max_canvas_width * height_scale / width_scale
        else:
            self.scale = width_scale
            self.canvas_width = max_canvas_width
            self.canvas_height = max_canvas_height * width_scale / height_scale
        
    # draw current solution ----------------------
    def draw_current_solution(self):
        # initialize solution instance
        solution = self.solution_list[self.cnt]
        # draw container1
        if self.draw_flag == False:
            self.container1 = self.canvas1.create_rectangle(WINDOW_MARGIN, WINDOW_MARGIN,
                                                          solution.strip_width * self.scale+WINDOW_MARGIN, 
                                                          self.strip_height * self.scale+WINDOW_MARGIN,
                                                          fill='gainsboro')
        else:
            self.canvas1.coords(self.container1, WINDOW_MARGIN, WINDOW_MARGIN,
                               solution.strip_width * self.scale+WINDOW_MARGIN, 
                               self.strip_height * self.scale+WINDOW_MARGIN)
        # draw pieces        
        for i in range(solution.move_num):
            # initialize location instance
            location = solution.location_list[i]
            if location.placement == 1:
                # set color
                if location.overlap == 0:
                    color = 'dodgerblue'
                else:
                    color = 'gold'
                # set polygon
                polygon = self.piece_list[location.idx].shape_list[location.mode]
                coord_list = []
                for j in range(polygon.vertex_num):
                    x = location.x + polygon.x_list[j]
                    y = location.y + polygon.y_list[j]
                    coord_list.append(x * self.scale+WINDOW_MARGIN)
                    coord_list.append((self.strip_height - y) * self.scale+WINDOW_MARGIN)
                # draw piece
                if self.draw_flag == False:
                    figure = self.canvas1.create_polygon(coord_list, fill=color, outline='black')
                    self.figure_list1.append(figure)
                else:
                    self.canvas1.itemconfigure(self.figure_list1[location.idx], fill=color)
                    self.canvas1.coords(self.figure_list1[location.idx], _flatten(coord_list))
        # update canvas
        self.canvas1.update()
        # show numerical data
        width_label = 'width: %.3f' % solution.strip_width
        util_label = ' (%.3f%%)\n' % solution.utilization
        iter_label = 'frame: %d / %d' % (self.cnt+1, self.solution_num)
        self.data_label1.configure(text=width_label+util_label+iter_label)
        # set draw flag
        self.draw_flag = True

    # draw feasible solution ---------------------
    def draw_feasible_solution(self):
        # initialize solution instance
        solution = self.complete_solution
        # draw container2
        if self.fs_draw_flag == False:
            self.container2 = self.canvas2.create_rectangle(WINDOW_MARGIN, WINDOW_MARGIN,
                                                          solution.strip_width * self.scale+WINDOW_MARGIN, 
                                                          self.strip_height * self.scale+WINDOW_MARGIN,
                                                          fill='gainsboro')        
        else:
            self.canvas2.coords(self.container2, WINDOW_MARGIN, WINDOW_MARGIN,
                               solution.strip_width * self.scale+WINDOW_MARGIN, 
                               self.strip_height * self.scale+WINDOW_MARGIN)        
        # draw pieces
        for i in range(self.piece_num):
            # initialize location instance
            location = solution.location_list[i]
            if location.placement == 1:
                # set color
                if location.overlap == 0:
                    color = 'dodgerblue'
                else:
                    color = 'gold'
                # set polygon
                polygon = self.piece_list[location.idx].shape_list[location.mode]
                coord_list = []
                for j in range(polygon.vertex_num):
                    x = location.x + polygon.x_list[j]
                    y = location.y + polygon.y_list[j]
                    coord_list.append(x * self.scale+WINDOW_MARGIN)
                    coord_list.append((self.strip_height - y) * self.scale+WINDOW_MARGIN)
                # draw piece
                if self.fs_draw_flag == False:
                    figure = self.canvas2.create_polygon(coord_list, fill=color, outline='black')
                    self.figure_list2.append(figure)
                else:
                    self.canvas2.itemconfigure(self.figure_list2[location.idx], fill=color)
                    self.canvas2.coords(self.figure_list2[location.idx], _flatten(coord_list))
        # update canvas
        self.canvas2.update()
        # show numerical data
        width_label = 'width: %.3f' % solution.strip_width
        util_label = ' (%.3f%%)\n' % solution.utilization
        iter_label = 'frame: %d / %d' % (self.cnt+1, self.solution_num)
        self.data_label2.configure(text=width_label+util_label+iter_label)
        # set draw flag
        self.fs_draw_flag = True
        pass

    # update complete solution -------------------
    def update_complete_solution(self):
        # update location of pieces
        for location in self.solution_list[self.cnt].location_list:
            self.complete_solution.location_list[location.idx] = copy.deepcopy(location)
        # update strip_width
        self.complete_solution.strip_width = self.solution_list[self.cnt].strip_width
        # update utilization
        self.complete_solution.utilization = self.solution_list[self.cnt].utilization
        # set move_num
        self.complete_solution.move_num = self.piece_num
            
    # check feasibility --------------------------
    def check_feasible(self):
        fs_flag = True
        # check feasibility
        for location in self.complete_solution.location_list:
            if location.overlap == 1:
                fs_flag = False
                break
        # return value
        return fs_flag

# --------------------------------------------------------------------
# main
# --------------------------------------------------------------------
def main():
    demo = Demo()
    demo.mainloop()

# --------------------------------------------------------------------
# call main function
# --------------------------------------------------------------------
if __name__ == "__main__":
  main()

# --------------------------------------------------------------------
# end of file
# --------------------------------------------------------------------

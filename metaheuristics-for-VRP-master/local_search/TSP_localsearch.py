import copy
import random
import math

class Life:
      """个体类"""
      def __init__(self, gene = None):
            self.gene = gene
            self.score = -1

class LS:
    """局部搜索类"""
    def __init__(self, length, scorefun):
        self.length = length #样本长度
        self.termination = False #终止状态为false
        self.scorefun = scorefun
        self.initialize() #生成初始解
    
    # 初始化，生成一个样本,并计算分数
    def initialize(self):
        gene = list(range(self.length))
        random.shuffle(gene)
        life = Life(gene)
        self.life = life
        self.life.score = self.scorefun(life)
        
    # 生成最好的neighbor(2-opt)
    def localsearch(self):
        self.best = self.life
        for i in range(self.length):
            for j in range(i+1,self.length):
                life_temp = copy.deepcopy(self.life) #深拷贝以免影响父本
                life_temp.gene[i], life_temp.gene[j] = life_temp.gene[j], life_temp.gene[i]
                life_temp.score = self.scorefun(life_temp)
                if self.best.score < life_temp.score:
                    self.best = life_temp
    
    # 判断是否终止
    def isterminated(self):
        if self.best.score > self.life.score:
            self.termination = False
        else:
            self.termination = True
        self.life = self.best

class TSP:
    def __init__(self):
    	self.initcitys()
    	self.ls = LS(length = len(self.citys), scorefun = self.scorefun())

    def initcitys(self):
        self.citys = []
        """
        for i in range(34):
              x = random.randint(0, 1000)
              y = random.randint(0, 1000)
              self.citys.append((x, y))
        """

        #中国34城市经纬度
        self.citys.append((116.46, 39.92))
        self.citys.append((117.2,39.13))
        self.citys.append((121.48, 31.22))
        self.citys.append((106.54, 29.59))
        self.citys.append((91.11, 29.97))
        self.citys.append((87.68, 43.77))
        self.citys.append((106.27, 38.47))
        self.citys.append((111.65, 40.82))
        self.citys.append((108.33, 22.84))
        self.citys.append((126.63, 45.75))
        self.citys.append((125.35, 43.88))
        self.citys.append((123.38, 41.8))
        self.citys.append((114.48, 38.03))
        self.citys.append((112.53, 37.87))
        self.citys.append((101.74, 36.56))
        self.citys.append((117,36.65))
        self.citys.append((113.6,34.76))
        self.citys.append((118.78, 32.04))
        self.citys.append((117.27, 31.86))
        self.citys.append((120.19, 30.26))
        self.citys.append((119.3, 26.08))
        self.citys.append((115.89, 28.68))
        self.citys.append((113, 28.21))
        self.citys.append((114.31, 30.52))
        self.citys.append((113.23, 23.16))
        self.citys.append((121.5, 25.05))
        self.citys.append((110.35, 20.02))
        self.citys.append((103.73, 36.03))
        self.citys.append((108.95, 34.27))
        self.citys.append((104.06, 30.67))
        self.citys.append((106.71, 26.57))
        self.citys.append((102.73, 25.04))
        self.citys.append((114.1, 22.2))
        self.citys.append((113.33, 22.13))

    def distance(self, order):
        distance = 0.0
        for i in range(-1, len(self.citys) - 1):
            index1, index2 = order[i], order[i + 1]
            city1, city2 = self.citys[index1], self.citys[index2]
            distance += math.sqrt((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2)
        return distance

    def scorefun(self):
    	return lambda life: 1.0/self.distance(life.gene) # x是城市顺序

    def run(self):
        i = 0
        while not self.ls.termination:
            self.ls.localsearch()
            self.ls.isterminated()
            distance = self.distance(self.ls.life.gene)
            print(("%d: %f") % (i, distance))
            i += 1

def main():
    tsp = TSP()
    tsp.run()

if __name__ == '__main__':
    main()
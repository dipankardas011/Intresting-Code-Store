import matplotlib.pyplot as plt
from plotly.graph_objs import Bar, Layout
from plotly import offline

def exec (seed):
    """the user will enter a seed for each seed"""
    for i in range(seed):
        inp=input("enter the seed.. ")
        
        n=int(inp)
        x=1
        steps=list()
        yval=list()
        while n>1:
            # steps appended inside
            # yval appended inside
            yval.append(n)
            steps.append(x)
            print(n,end=" ")
            if n%2 == 0:
                # even
                n = n//2
            else:
                n = 3*n+1

            x+=1
        print("1")
        # steps appended inside
        # yval appended inside
        steps.append(x)
        yval.append(int(1))

        plt.style.use('seaborn')
        fig, ax=plt.subplots()
        ax.scatter(steps, yval,c="Green",s=10)
        
        ax.set_title(f"3*N+1 problem with seed = {inp}",fontsize=24)
        ax.set_ylabel("values",fontsize=14)
        ax.set_xlabel("Step no", fontsize=14)
        ax.axis([0,max(steps),0,max(yval)])
        plt.show()
        plt.savefig(f'3N+1 {i+1}.png',bbox_inches='tight')

        data=[Bar(x=steps, y=yval)]
        xx={'title':'Step no', 'dtick':5}
        yy={'title':'values'}
        mylayout=Layout(title=f"3*N+1 problem with seed = {inp}", xaxis=xx, yaxis=yy)
        offline.plot({'data':data, 'layout':mylayout} ,filename=f'dw{i+1}.html')


    print("EXIT Code: 0x0")

if __name__=="__main__":
    print("Welcome to 3*N+1 problem solver...")
    test = input("Enter the number of test cases... ")
    # test cases
    exec(int(test))
    print("EXIT Code: 0x1")
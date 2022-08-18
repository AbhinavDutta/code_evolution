#calculate n^2 jaccard values and create companion of every file
import sys
import glob
import os
import shutil
import git 
import subprocess

if os.path.exists("code_evolution"):
    shutil.rmtree("code_evolution")
if os.path.exists("commit_history"):
    shutil.rmtree("commit_history")
if os.path.exists("ast_commit_history"):
    shutil.rmtree("ast_commit_history")

os.mkdir("code_evolution")
os.mkdir("commit_history")
os.mkdir("ast_commit_history")

def extract(directory):
    #looks at the sync folder , creates our own folder of exercises
    files = glob.glob(directory + '/**/*.ml',recursive=True)
    for fname in files:
        #fname looks like /home/abhinav/Desktop/mitacs/code/sync/ZRH/M3K/FL9/TOO/hw1.ml

        fname_str = str(fname)
        print(fname_str+"\n")
        if(fname_str[0] == 'X' and fname_str[1] == '/'):
            continue


        stud_id = fname_str.split('/')
        #stud_id looks like ['', 'home', 'abhinav', 'Desktop', 'mitacs', 'code', 'sync', 'ZRH', 'M3K', 'FL9', 'TOO', 'hw1.ml']

        exercise_name = ''
        token=stud_id[len(stud_id)-5]+stud_id[len(stud_id)-4]+stud_id[len(stud_id)-3]+stud_id[len(stud_id)-2]
        #token looks like ZRHM3KFL9TOO

        #creating a directory for each exercise
        exercise_name = (stud_id[len(stud_id)-1]).split('.',1)[0]

        if not os.path.exists("code_evolution/"+exercise_name):
            os.mkdir("code_evolution/"+exercise_name)
        if not os.path.exists("commit_history/"+exercise_name):
            os.mkdir("commit_history/"+exercise_name)
        if not os.path.exists("ast_commit_history/"+exercise_name):
            os.mkdir("ast_commit_history/"+exercise_name)
        
        dir_name=""
        for i in range(0,len(stud_id)-1):
            dir_name=dir_name+stud_id[i]+"/"
        #dir_name looks like /home/abhinav/Desktop/mitacs/code/sync/ZRH/M3K/FL9/TOO/

        curr_repo = git.Repo(dir_name)
        string_commit = curr_repo.git.log(exercise_name+'.ml',pretty='format:%h')
        commit_list = string_commit.split('\n')


        
        edit_script_name = "code_evolution/"+exercise_name+"/"+token+".txt"
        edit_script = open(edit_script_name,"w")
        edit_script.close()

        curr_code_name="code_evolution/"+exercise_name+"/"+token+"."+str(0)+"."+commit_list[0]+".ml"
        version_contents = curr_repo.git.show(commit_list[0]+":./"+exercise_name+".ml")
        curr_code = open(curr_code_name, "w")
        curr_code.write(version_contents)
        curr_code.close()

        #return_code = subprocess.call("gumtree parse "+curr_code_name+" >> "+edit_script_name , shell=True)
        #return_code = subprocess.call("echo '\n' "+" >> "+edit_script_name , shell=True)
        os.remove(curr_code_name)

        for i in range(0,len(commit_list)):
            commit = commit_list[i]
            version_contents = curr_repo.git.show(commit+":./"+exercise_name+".ml")
            curr_code_name="commit_history/"+exercise_name+"/"+token+"."+str(i)+"."+commit+".ml"

            curr_code = open(curr_code_name, "w")
            curr_code.write(version_contents)
            curr_code.close()
            

        for i in range(0,len(commit_list)):
            commit = commit_list[i]
            curr_code_name="commit_history/"+exercise_name+"/"+token+"."+str(i)+"."+commit+".ml"
            ast_file_name = "ast_commit_history/"+exercise_name+"/"+token+"."+str(i)+".ml";
            return_code = subprocess.call("gumtree parse "+curr_code_name+" >> "+ast_file_name , shell=True)



        first_code_name="commit_history/"+exercise_name+"/"+token+"."+str(0)+"."+commit_list[0]+".ml"
        subprocess.call("gumtree textdiff "+first_code_name+" "+"blank.ml"+" >> "+edit_script_name , shell=True)
          
        for i in range(1,len(commit_list)):
            print(token+"\t diff between version "+str(i)+" and "+str(i-1))
            commit = commit_list[i]
            prev_commit = commit_list[i-1]
            curr_code_name="commit_history/"+exercise_name+"/"+token+"."+str(i)+"."+commit+".ml"
            prev_code_name="commit_history/"+exercise_name+"/"+token+"."+str(i-1)+"."+prev_commit+".ml"
           

            return_code = subprocess.call("gumtree textdiff "+prev_code_name+" "+curr_code_name+" >> "+edit_script_name , shell=True)
            #return_code = subprocess.call("gumtree textdiff "+prev_code_name+" "+curr_code_name, shell=True)
            #print("gumtree textdiff "+prev_code_name+" "+curr_code_name+" >> "+edit_script_name)
            curr_code.close() 

        

directory=""      
if(len(sys.argv)>1):
    directory=sys.argv[1]
else:
    directory="/home/abhinav/Desktop/mitacs/code/sync_old"

extract(directory)

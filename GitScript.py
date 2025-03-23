# import argparse
# import subprocess
# import sys
import argparse
import subprocess

def run_command(command, allow_input=False):
    """执行 shell 命令。如果 allow_input=True，则允许用户手动输入密码"""
    process = subprocess.Popen(command, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    if allow_input:
        ssh_password = input("🔑 请输入 SSH 私钥密码：") + "\n"
        process.stdin.write(ssh_password)
        process.stdin.flush()

    stdout, stderr = process.communicate()
    if stdout:
        print(stdout)
    if stderr:
        print(stderr)

def main():
    parser = argparse.ArgumentParser(description="Git 提交脚本，支持 SSH 密钥密码输入")
    parser.add_argument("-m", required=True, help="commit 信息")
    parser.add_argument("-b", default="main", help="提交的分支，默认为 main")

    args = parser.parse_args()
    branch = args.b
    commit_message = args.m

    print("\n执行 Git 提交流程:")
    print("1. 添加所有更改")
    run_command("git add .")

    print("2. 提交代码")
    run_command(f'git commit -m "{commit_message}"')

    print("3. 推送到远程分支")
    run_command(f"git push origin {branch}", allow_input=True)

    print("\n✅ Git 提交完成！")

if __name__ == "__main__":
    main()
#
# def run_command(command):
#     """执行 shell 命令并打印输出"""
#     result = subprocess.run(command, shell=True, capture_output=True, text=True)
#     if result.stdout:
#         print(result.stdout)
#     if result.stderr:
#         print(result.stderr, file=sys.stderr)
#
# def main():
#     parser = argparse.ArgumentParser(description="Git 提交脚本，自动执行 git add、commit 和 push")
#     parser.add_argument("-m", required=True, help="commit 信息")
#     parser.add_argument("-b", default="main", help="提交的分支，默认为 main")
#
#     args = parser.parse_args()
#
#     branch = args.b
#     commit_message = args.m
#
#     print("\n执行 Git 提交流程:")
#     print("1. 添加所有更改")
#     run_command("git add .")
#
#     print("2. 提交代码")
#     run_command(f"git commit -m \"{commit_message}\"")
#
#     print("3. 推送到远程分支")
#     run_command(f"git push origin {branch}")
#
#     print("\n✅ Git 提交完成！")

# if __name__ == "__main__":
#     main()

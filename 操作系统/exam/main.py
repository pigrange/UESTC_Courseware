import sys


class Process:
    def __init__(self, name, priority, status='ready'):
        self.name = name
        self.priority = priority
        if name == 'init':
            self.parent = None
        else:
            self.parent = running
        self.status = status
        self.child = []
        self.request = [0, 0, 0, 0]
        self.resource = [0, 0, 0, 0]


class Resource:
    def __init__(self, max_num):
        self.max_num = max_num
        self.available = max_num
        self.wait_list = []


instructions = []
process_0 = None
processes_1 = []
processes_2 = []
resources = []
count_1 = 0
count_2 = 0
blocked_list = []
running = None


def init():
    global process_0, resources

    pro = Process('init', 0)
    process_0 = pro
    pro.status = 'running'
    global running
    running = pro

    R1 = Resource(1)
    R2 = Resource(2)
    R3 = Resource(3)
    R4 = Resource(4)
    resources = [R1, R2, R3, R4]

    print(running.name, end=' ')


def get_instructions(file_path):
    f = open(file_path, mode='r', encoding='gb2312')
    context = f.read()
    instructions.extend(context.split('\n'))
    f.close()


def execute(instruction):
    global running

    type_ins = instruction.split()[0]
    if type_ins == 'cr':
        name = instruction.split()[1]
        priority = int(instruction.split()[2])
        create_process(name, priority)
    elif type_ins == 'to':
        time_out()
    elif type_ins == 'de':
        name = instruction.split()[1]
        pro = get_process(name)
        destroy_process(pro)
    elif type_ins == 'req':
        res_type = instruction.split()[1]
        num = int(instruction.split()[2])
        request_res(running, res_type, num)
    elif type_ins == 'rel':
        res_type = instruction.split()[1]
        num = int(instruction.split()[2])
        release_part_res(running, res_type, num)


def create_process(name, priority):
    pre_priority = running.priority
    pro = Process(name, priority)
    running.child.append(pro)

    if priority == 1:
        insert_process_to_ready(1, pro)
    elif priority == 2:
        insert_process_to_ready(2, pro)
        if pre_priority == 1:
            global count_1
            count_1 += 1
            count_1 %= len(processes_1)

    run_next_process('ready')
    print(running.name, end=' ')


def insert_process_to_ready(priority, pro):
    global count_1, count_2
    if priority == 1:
        if count_1 == 0:
            processes_1.append(pro)
        else:
            index = count_1 % len(processes_1)
            processes_1.insert(index, pro)
            count_1 += 1
    elif priority == 2:
        if count_2 == 0:
            processes_2.append(pro)
        else:
            index = count_2 % len(processes_2)
            processes_2.insert(index, pro)
            count_2 += 1


def run_next_process(status):
    global count_1, count_2, running

    if len(processes_1) == 0 and len(processes_2) == 0:
        running = process_0
    elif len(processes_2) > 0:
        running.status = status
        processes_2[count_2].status = 'running'
        running = processes_2[count_2]
    else:
        running.status = status
        processes_1[count_1].status = 'running'
        running = processes_1[count_1]


def time_out():
    global count_1, count_2

    if running.priority == 1:
        count_1 += 1
        count_1 %= len(processes_1)
    elif running.priority == 2:
        count_2 += 1
        count_2 %= len(processes_2)

    run_next_process('ready')
    print(running.name, end=' ')


def get_process(name):
    for i in range(len(processes_1)):
        if name == processes_1[i].name:
            return processes_1[i]
    for j in range(len(processes_2)):
        if name == processes_2[j].name:
            return processes_2[j]
    for k in range(len(blocked_list)):
        if name == blocked_list[k].name:
            return blocked_list[k]


def remove_process(pro, queue='ready', status='ready'):
    global count_1, count_2

    if pro in processes_1:
        global count_1
        idx = processes_1.index(pro)
        processes_1.remove(pro)
        if idx < count_1:
            count_1 -= 1
        elif count_1 == len(processes_1):
            count_1 = 0
    if pro in processes_2:
        global count_2
        idx = processes_2.index(pro)
        processes_2.remove(pro)
        if idx < count_2:
            count_2 -= 1
        elif count_2 == len(processes_2):
            count_2 = 0
    if queue == 'all':
        if pro.status == 'blocked':
            blocked_list.remove(pro)
    if pro == running:
        run_next_process(status)


def destroy_process(pro, is_print=True):
    if len(pro.child) is not 0:
        for i in range(len(pro.child)):
            destroy_process(pro.child[i], is_print=False)
        pro.child.clear()

    if pro.resource != [0, 0, 0, 0]:
        release_all_res(pro)
    activate_blocked_process()
    remove_process(pro, queue='all')

    if is_print:
        print(running.name, end=' ')


def request_res(pro, res_type, num):
    global resources
    res_type = int(res_type[1]) - 1
    r = resources[res_type]

    if num > r.max_num:
        print('Resource number Error!')
    else:
        if r.available >= num:
            r.available -= num
            pro.resource[res_type] = num
        else:
            r.wait_list.append(pro)
            pro.status = 'blocked'
            pro.request[res_type] = num
            blocked_list.append(pro)
            remove_process(pro, status='blocked')

    print(running.name, end=' ')


def release_all_res(pro):
    for i in range(4):
        if pro.resource[i] > 0:
            num = pro.resource[i]
            resources[i].available += num
            pro.resource[i] = 0


def release_part_res(pro, res_type, num):
    res_type = int(res_type[1]) - 1
    r = resources[res_type]

    if num <= pro.resource[res_type]:
        pro.resource[res_type] -= num
        r.available += num
    else:
        print("Number error!")

    activate_blocked_process()
    run_next_process('ready')
    print(running.name, end=' ')


def activate_blocked_process():
    global blocked_list
    while len(blocked_list) != 0:
        pro = blocked_list[0]
        for j in range(4):
            r = resources[j]
            request_num = pro.request[j]
            if 0 < request_num <= r.available:
                r.available -= request_num
                pro.resource[j] += request_num
                pro.request[j] = 0
                r.wait_list.remove(pro)

        if pro.request == [0, 0, 0, 0]:
            pro.status = 'ready'
            if pro.priority == 1:
                insert_process_to_ready(1, pro)
            elif pro.priority == 2:
                insert_process_to_ready(2, pro)
            blocked_list.remove(pro)
        else:
            return


if __name__ == '__main__':
    init()
    get_instructions(sys.argv[1])
    num_instructions = len(instructions)
    for ii in range(num_instructions):
        if ii == 13:
            a = 1
        execute(instructions[ii])

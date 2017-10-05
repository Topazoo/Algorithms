class monitor:
    def __init__(self):
        self.proposed = []
        self.engaged = 'None'

women_rankings = {
    'Kat': {
        'David': 5,
        'Sam': 7,
        'Tyler': 3,
        'Wilson': 10,
        'Ezekiel': 1,
        'Jimothy': 6
    },
    'Sarah': {
        'David': 6,
        'Sam': 4,
        'Tyler': 5,
        'Wilson': 9,
        'Ezekiel': 7,
        'Jimothy': 5
    },
    'Trixie': {
        'David': 9,
        'Sam': 5,
        'Tyler': 5,
        'Wilson': 3,
        'Ezekiel': 9,
        'Jimothy': 3
    },
    'Lisa': {
        'David': 5,
        'Sam': 7,
        'Tyler': 3,
        'Wilson': 10,
        'Ezekiel': 1,
        'Jimothy': 6
    },
    'Hannah': {
        'David': 6,
        'Sam': 5,
        'Tyler': 9,
        'Wilson': 1,
        'Ezekiel': 4,
        'Jimothy': 2
    },
    'Spuds': {
        'David': 2,
        'Sam': 4,
        'Tyler': 7,
        'Wilson': 1,
        'Ezekiel': 2,
        'Jimothy': 8
    },
}

men_rankings = {
    'David': {
        'Kat': 8,
        'Sarah': 6,
        'Trixie': 2,
        'Lisa': 10,
        'Hannah': 6,
        'Spuds': 1
    },
    'Sam': {
        'Kat': 7,
        'Sarah': 5,
        'Trixie': 5,
        'Lisa': 8,
        'Hannah': 3,
        'Spuds': 2
    },
    'Tyler': {
        'Kat': 9,
        'Sarah': 8,
        'Trixie': 1,
        'Lisa': 5,
        'Hannah': 6,
        'Spuds': 3
    },
    'Wilson': {
        'Kat': 3,
        'Sarah': 9,
        'Trixie': 10,
        'Lisa': 5,
        'Hannah': 3,
        'Spuds': 9
    },
    'Ezekiel': {
        'Kat': 6,
        'Sarah': 8,
        'Trixie': 6,
        'Lisa': 10,
        'Hannah': 7,
        'Spuds': 3
    },
    'Jimothy': {
        'Kat': 2,
        'Sarah': 5,
        'Trixie': 9,
        'Lisa': 4,
        'Hannah': 10,
        'Spuds': 5
    },
}

women = {
    'Kat': monitor(),
    'Sarah': monitor(),
    'Trixie': monitor(),
    'Lisa': monitor(),
    'Hannah': monitor(),
    'Spuds':monitor()
}
men = {
    'David': monitor(),
    'Sam': monitor(),
    'Tyler': monitor(),
    'Wilson': monitor(),
    'Ezekiel': monitor(),
    'Jimothy': monitor()
}

def all_eng():
    for name, monitor in men.items():
        if monitor.engaged == 'None':
            return (name, monitor)

    return False

def print_matches(men):
    for name, monitor in men.items(): #Print results
        print name,'is engaged to', monitor.engaged

def stable_match_couples(men, women, men_rankings, women_rankings):
    while 1:
        check = all_eng() #Get unmatched man or terminate

        if not check:
            break
        
        name = check[0]
        monitor = check[1]
        highest_ranked = 'None'
        
        if set(monitor.proposed) != set([key for key in women]):
            
            for woman in men_rankings[name].items(): #Get top woman who hasn't been proposed to 
                if highest_ranked == 'None' and woman[0] not in monitor.proposed:
                    highest_ranked = woman
                elif highest_ranked != 'None' and highest_ranked[1] < woman[1] and woman[0] not in monitor.proposed:
                    highest_ranked = woman

            monitor.proposed.append(highest_ranked[0])
            women[highest_ranked[0]].proposed.append(name)

            if women[highest_ranked[0]].engaged == 'None':
                women[highest_ranked[0]].engaged = name #If umnarried, get engaged
                monitor.engaged = highest_ranked[0]

            else:
                if women_rankings[highest_ranked[0]][name] > women_rankings[highest_ranked[0]][women[highest_ranked[0]].engaged]:
                    monitor.engaged = 'None' #If married but unmatched man higher rank, get engaged
                    women[highest_ranked[0]].engaged = name

    print_matches(men)

stable_match_couples(men, women, men_rankings, women_rankings)           

            
                

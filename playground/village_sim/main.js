const JOBS = {
  Farmer: {
    produce: { food: 4 },
    flavor: "tends the communal fields"
  },
  Gatherer: {
    produce: { water: 4 },
    flavor: "draws fresh water from the spring"
  },
  Carpenter: {
    produce: { beds: 1 },
    flavor: "maintains the sleeping quarters"
  },
  Cook: {
    produce: { food: 2, water: 1 },
    flavor: "prepares hearty meals"
  },
  Caretaker: {
    produce: { beds: 1 },
    flavor: "keeps the bunks tidy"
  }
};

const NEED_NAMES = ["food", "water", "sleep"];

const MAX_NEED = 100;
const NEED_DECAY = 7;
const CONSUME_AMOUNT = 40;

const STARTING_AGENTS = [
  { name: "Alena", job: "Farmer" },
  { name: "Bran", job: "Gatherer" },
  { name: "Caro", job: "Cook" },
  { name: "Dela", job: "Carpenter" },
  { name: "Eryn", job: "Farmer" },
  { name: "Finn", job: "Caretaker" }
];

class Agent {
  constructor({ name, job }) {
    this.name = name;
    this.job = job;
    this.needs = {
      food: MAX_NEED,
      water: MAX_NEED,
      sleep: MAX_NEED
    };
    this.energy = 100;
    this.lastAction = "arrived";
  }

  tick(village, log) {
    NEED_NAMES.forEach(need => {
      this.needs[need] = Math.max(0, this.needs[need] - NEED_DECAY);
    });

    const criticalNeed = NEED_NAMES.find(need => this.needs[need] <= 40);
    if (criticalNeed) {
      this.tryConsumeNeed(criticalNeed, village, log);
      return;
    }

    this.performJob(village, log);
  }

  tryConsumeNeed(need, village, log) {
    const storeKey = need === "sleep" ? "beds" : need;
    if (village.resources[storeKey] > 0) {
      village.resources[storeKey] -= 1;
      this.needs[need] = Math.min(MAX_NEED, this.needs[need] + CONSUME_AMOUNT);
      this.lastAction = `used ${storeKey}`;
      log.push(`${this.name} restores ${need} by using ${storeKey}.`);
    } else {
      this.lastAction = `needs ${need}`;
      log.push(`${this.name} cannot find ${storeKey} and grows weaker.`);
    }
  }

  performJob(village, log) {
    const job = JOBS[this.job];
    if (!job) return;

    Object.entries(job.produce).forEach(([resource, amount]) => {
      village.resources[resource] = Math.min(
        village.storageLimits[resource],
        village.resources[resource] + amount
      );
    });

    this.lastAction = job.flavor;
    log.push(`${this.name} ${job.flavor}.`);
  }
}

class Village {
  constructor() {
    this.resources = {
      food: 6,
      water: 6,
      beds: 3
    };
    this.storageLimits = {
      food: 40,
      water: 40,
      beds: 12
    };
    this.tick = 0;
    this.agents = STARTING_AGENTS.map(agent => new Agent(agent));
    this.log = ["The sun rises over the valley. The village awakens."];
  }

  step() {
    this.tick += 1;
    const frameLog = [`Day ${this.tick}`];

    this.agents.forEach(agent => agent.tick(this, frameLog));

    this.log = frameLog.concat(this.log).slice(0, 60);
    return frameLog;
  }
}

const village = new Village();
const resourcePanel = document.getElementById("resource-panel");
const villageGrid = document.getElementById("village-grid");
const logPanel = document.getElementById("log");
const toggleButton = document.getElementById("toggle-sim");
const stepButton = document.getElementById("step-sim");
const tickDisplay = document.getElementById("tick-display");

let intervalId = null;

function renderResources() {
  resourcePanel.innerHTML = "";
  Object.entries(village.resources).forEach(([resource, value]) => {
    const limit = village.storageLimits[resource];
    const card = document.createElement("div");
    card.className = "resource-card";
    card.innerHTML = `
      <h3>${resource.toUpperCase()}</h3>
      <strong>${value} / ${limit}</strong>
      <progress max="${limit}" value="${value}"></progress>
    `;
    resourcePanel.appendChild(card);
  });
}

function renderAgents() {
  villageGrid.innerHTML = "";
  village.agents.forEach(agent => {
    const card = document.createElement("div");
    card.className = "agent-card";

    const header = document.createElement("div");
    header.className = "agent-header";
    header.innerHTML = `
      <h3>${agent.name}</h3>
      <span class="agent-job">${agent.job}</span>
    `;

    const needs = document.createElement("div");
    NEED_NAMES.forEach(need => {
      const row = document.createElement("div");
      row.className = "need-row";
      const label = need[0].toUpperCase() + need.slice(1);
      row.innerHTML = `
        <span>${label}</span>
        <progress max="${MAX_NEED}" value="${agent.needs[need]}"></progress>
      `;
      needs.appendChild(row);
    });

    const status = document.createElement("span");
    status.className = "status-tag";
    status.textContent = agent.lastAction;

    card.appendChild(header);
    card.appendChild(needs);
    card.appendChild(status);

    villageGrid.appendChild(card);
  });
}

function renderLog() {
  logPanel.innerHTML = "";
  village.log.forEach(entry => {
    const paragraph = document.createElement("p");
    paragraph.className = "log-entry";
    paragraph.textContent = entry;
    logPanel.appendChild(paragraph);
  });
}

function renderAll() {
  renderResources();
  renderAgents();
  renderLog();
  tickDisplay.textContent = `Day ${village.tick}`;
}

function stepSimulation() {
  village.step();
  renderAll();
}

toggleButton.addEventListener("click", () => {
  if (intervalId) {
    clearInterval(intervalId);
    intervalId = null;
    toggleButton.textContent = "Start";
  } else {
    stepSimulation();
    intervalId = setInterval(stepSimulation, 1500);
    toggleButton.textContent = "Pause";
  }
});

stepButton.addEventListener("click", () => {
  if (intervalId) return;
  stepSimulation();
});

renderAll();

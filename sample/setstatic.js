const chroma = require('../index')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  chroma.Keyboard.setStatic({red: 255, green: 0, blue: 0});
  utils.pressKeyToExit(chroma)
} else {
  console.log(`Failed to initialize!`)
}

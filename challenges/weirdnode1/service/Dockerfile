FROM node:alpine
WORKDIR /usr/src/app
COPY package*.json ./
COPY ./challenge.js .
COPY ./flag.js .
RUN npm install
EXPOSE 31337
CMD ["npm", "start"]
